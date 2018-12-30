// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Character.h"
#include "BatteryCollector.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PrimaryActorTick.bStartWithTickEnabled = true;
		PrimaryActorTick.bCanEverTick = true; //tick is set to false in gamemodebase
	}

	//base decay rate
	DecayRate = 0.01f;
}


void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	//find all spawn volume AActors
	for (TActorIterator<ASpawnVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SpawnVolumeActors.AddUnique(*ActorItr);
	}

	SetCurrentState(EBatteryPlayState::EPlaying);

	//set the score to beat
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower()) * PowerToWinScalar;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check using a battery collector character
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
		
	{

		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}
		//If power is greater than 1. Does not seem to work if set to 0
		else if (MyCharacter->GetCurrentPower() > 1.0f)
		{
			//decrease the character's power using the decay rate
			MyCharacter->UpdatePower(-DeltaTime*DecayRate*(MyCharacter->GetCurrentPower()));
		}
		else
		{

			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
	
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	//handle the new current state
	HandleNewState(CurrentState);
}


void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		//IF the game is playing
	case EBatteryPlayState::EPlaying:
		{
		//spawn volumes active
			for (ASpawnVolume* SpawnVolume : SpawnVolumeActors)
			{
				SpawnVolume->SetSpawningActive(true);
			}
		}
		break;
		//Won the game
		case EBatteryPlayState::EWon:
		{
			// spawn volumes inactive
			for (ASpawnVolume* SpawnVolume : SpawnVolumeActors)
			{
				SpawnVolume->SetSpawningActive(false);
			}
		}
		break;
		//Lost the game
		case EBatteryPlayState::EGameOver:
		{
			// spawn volumes inactive
			for (ASpawnVolume* SpawnVolume : SpawnVolumeActors)
			{
				SpawnVolume->SetSpawningActive(false);
			}
			//block player input
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				PlayerController->SetCinematicMode(true, false, false, true, true);
			}
			//ragdoll the character
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter)
			{
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}
		break;
		//Unknown/default state
		default:
		case EBatteryPlayState::EUnknown:
		{
			//do a debug message
			UE_LOG(LogTemp, Warning, TEXT("Unknown state"));
		}
		break;
	}
}