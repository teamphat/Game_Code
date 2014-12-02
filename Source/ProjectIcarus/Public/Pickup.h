a// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/**
 * Class representing an object that can be picked up
 */
UCLASS()
class PROJECTICARUS_API APickup : public AActor
{
	GENERATED_UCLASS_BODY()

		/** True when the pickup is able to be picked up, false if something deactivates the pickup. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		uint8 m_ownerID;

	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<USphereComponent> m_pCollider;

	/** Function to call when the Pickup is collected. */
	UFUNCTION(BlueprintNativeEvent)
		void OnPickedUp();
};
