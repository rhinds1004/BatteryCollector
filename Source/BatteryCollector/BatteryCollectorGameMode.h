// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

//enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};


UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns power needed to win - needed for the HUD */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	/** Returns current playing state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	/** Sets current playing state */
	void SetCurrentState(EBatteryPlayState NewState);

	
protected:
	/** The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float DecayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float PowerToWinScalar = 1.25f;

	/** Widget class to use for our HUD screen */
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** The instance of the HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

	virtual void BeginPlay() override;

private:
	/** Keeps track of the current playing state */
	EBatteryPlayState CurrentState;

};



