// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Altar1.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTICARUS_API AAltar1 : public AActor
{
	GENERATED_UCLASS_BODY()
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Powerup)
		bool powerupActive;
	
	UPROPERTY(VisibleDefaultsOnly, BluePrintReadOnly, Category = Powerup)
		TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadOnly, Category = Powerup)
		TSubobjectPtr<UStaticMeshComponent> AltarMesh;

	UFUNCTION(BlueprintNativeEvent)
	void OnAltar();
	
};
