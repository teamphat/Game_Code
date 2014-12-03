// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTICARUS_API ASpawnVolume : public AActor
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(VisibleInstanceOnly, Category = Spawning)
		TSubobjectPtr<UBoxComponent> WhereToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		TSubclassOf<class APickup> WhatToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeHigh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeLow;

	UFUNCTION(BlueprintPure, Category = Spawning)
		FVector GetRandomPointInVolume();

	virtual void Tick(float DeltaSeconds) override;

	static void DestroyPickup(APickup* i_pObj);
	
private:
	float SpawnNum;
	float NumSpawned;
	APickup* m_pSpawnedPickup;
	float GetRandomSpawnDelay();
	float SpawnDelay;
	float SpawnTime;
	void SpawnPickup();
	void rmPkp(APickup* i_pObj);
};
