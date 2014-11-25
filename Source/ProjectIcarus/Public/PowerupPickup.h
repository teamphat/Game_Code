// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Altar1.h"
#include "PowerupPickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTICARUS_API APowerupPickup : public AAltar1
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
		float PowerLevel;
	
	void OnAltar_Implementation() OVERRIDE;
};
