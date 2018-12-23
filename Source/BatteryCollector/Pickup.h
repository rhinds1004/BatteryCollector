// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Return the mesh for the pickup */
	FORCEINLINE class UStaticMeshComponent *GetMesh() const { return PickupMesh; }



	/**Returns if the pickup is active or not.  */
	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool IsActive();

	/*Allows other classes to safely change if the Pickup is active or not*/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetIsActive(bool NewPickupState);
private:
	/**static mesh to repressent the pickup in the level*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *PickupMesh;
	
};
