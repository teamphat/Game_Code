// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "Altar.h"
#include "CharacterInteractions.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTICARUS_API ACharacterInteractions : public AActor
{
	GENERATED_UCLASS_BODY()
		/** Pickup radius for the character **/
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		TSubobjectPtr<USphereComponent> m_pCollectionRadius;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Power)
		AAltar* m_pAltar;

	/** The Current Creep We are Carrying **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		APickup* m_pCurrentCarry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stun)
		float m_StunDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stun)
		bool m_bIsStunned;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stun)
		float m_stunTime;

	virtual void Tick(float DeltaSeconds) OVERRIDE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		TSubobjectPtr<class USphereComponent> CollectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
		float PowerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
		float SpeedFactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
		float BaseSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
		float BasePower;

	//virtual void Tick(float DeltaSounds) OVERRIDE;

	/** Function to pickup a creep **/
	UFUNCTION(BlueprintCallable, Category = Pickup)
		void GrabCreep();

	/** Function to drop a creep if one is picked up **/
	UFUNCTION(BlueprintCallable, Category = Pickup)
		void DropCreep();

	/** Function to attack another player **/
	UFUNCTION(BlueprintCallable, Category = Stun)
		void Punch();
	UFUNCTION(BlueprintCallable, Category = Stun)
		bool IsStunned();
protected:

	UFUNCTION(BlueprintCallable, Category = Power)
		void CollectPowerup();

	UFUNCTION(BlueprintImplementableEvent, Category = Power)
		void Powerup(float Power);


	/** Function to drop creep and get stunned when punched **/
	UFUNCTION(BlueprintCallable, Category = Stun)
		void Stun();
	
	
};
