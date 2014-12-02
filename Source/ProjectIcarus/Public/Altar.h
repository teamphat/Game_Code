// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Altar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTICARUS_API AAltar : public AActor
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerLevel)
		float PowerLevel;
		/** Simple collision primitive to use as the root component. */
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<UBoxComponent> m_pCollider;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<UBoxComponent> CollisionVolume;

	/** StaticMeshComponent to represent the pickup in the level. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<UStaticMeshComponent> AltarMesh;
	
	virtual void Tick(float DeltaSeconds) override;
	void AddPower();
};
