// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Altar.h"
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
		AActor* m_owner;
	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<USphereComponent> m_pCollider;
	/** StaticMeshComponent to represent the pickup in the level. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<UStaticMeshComponent> PickupMesh;

	/** Function to call when the Pickup is collected. */
	UFUNCTION(BlueprintNativeEvent)
		void OnPickedUp();
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable, Category = Power)
		bool Sacrifice();
	UFUNCTION(BlueprintCallable, Category = Power)
		void Drop();
	bool IsPickedUp() const;
private:
	bool m_bPickedUp;
	bool m_bDropped;
	bool m_bStunDrop;
	float dt;
};
