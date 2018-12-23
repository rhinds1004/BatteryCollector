// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"
#include "BatteryCollector.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
}

void ABatteryPickup::WasCollected_Implementation()
{
	//Use base pickup behavior. super calls the parent's base behavior
	Super::WasCollected_Implementation();

	//Destory the battery
	Destroy();
}

