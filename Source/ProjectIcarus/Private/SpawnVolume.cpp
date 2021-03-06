// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "SpawnVolume.h"
#include "Pickup.h"


ASpawnVolume::ASpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	SpawnNum(1),
	NumSpawned(0)
{
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
	SpawnDelayRangeLow = 0.5f;
	SpawnDelayRangeHigh = 1.0f;
	SpawnDelay = GetRandomSpawnDelay();
	
	PrimaryActorTick.bCanEverTick = true;
}
void ASpawnVolume::SpawnPickup()
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World && NumSpawned < SpawnNum)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;
			
			FVector SpawnLocation = GetRandomPointInVolume();
			//1211.911377 is x location
			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0;
			SpawnRotation.Pitch = 0;
			SpawnRotation.Roll = 0;
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParameters);
			NumSpawned++;
			//m_SpawnedList.Add(SpawnedPickup);
		}
	}
}

float ASpawnVolume::GetRandomSpawnDelay()
{
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector RandomLocation;
	float X, MinY, MinZ;
	float MaxY, MaxZ;

	FVector Origin;
	FVector BoxExtent;
	
	Origin = WhereToSpawn->Bounds.Origin;
	BoxExtent = WhereToSpawn->Bounds.BoxExtent;

	X = 1211.911377f;
	MinY = Origin.Y - BoxExtent.Y / 2;
	MinZ = Origin.Z - BoxExtent.Z / 2;

	MaxY = Origin.Y + BoxExtent.Y / 2;
	MaxZ = Origin.Z + BoxExtent.Z / 2;

	RandomLocation.X = X;
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);
	
	return RandomLocation;
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
	SpawnTime += DeltaSeconds;

	bool shouldSpawn = (SpawnTime > SpawnDelay);

	if(shouldSpawn)
	{
		SpawnPickup();
		SpawnTime -= SpawnDelay;

		SpawnDelay = GetRandomSpawnDelay();
	}

	
}
void ASpawnVolume::DestroyPickup(APickup* i_pObj)
{
	//rmPkp(i_pObj);
}
void ASpawnVolume::rmPkp(APickup* i_pObj)
{
	//if
}