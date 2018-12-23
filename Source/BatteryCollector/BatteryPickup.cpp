// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"
#include "BatteryCollector.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
}


