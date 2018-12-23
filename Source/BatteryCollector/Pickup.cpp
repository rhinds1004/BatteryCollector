// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//all pickups start as true
	bIsActive = true;

	//Create the static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	//by making rootcomponent any effects added are based on size and location of this static mesh
	SetRootComponent(PickupMesh);
	//RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Returns active state
bool APickup::IsActive()
{
	return bIsActive;
}

//Sets active state
void APickup::SetIsActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}


