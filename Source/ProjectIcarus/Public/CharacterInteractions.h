// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.h"
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
	/** The Current Creep We are Carrying **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		APickup* m_pCurrentCarry;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
		AActor* m_pAltar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stun)
		float m_StunDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stun)
		bool m_bIsStunned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stun)
		bool m_bIsPoweredUp;

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
	UFUNCTION(BlueprintCallable, Category = Pickup)
		void SetAltar(AActor* i_pActor);
	/** Function to drop a creep if one is picked up **/
	UFUNCTION(BlueprintCallable, Category = Pickup)
		void DropCreep();

	/** Function to attack another player **/
	UFUNCTION(BlueprintCallable, Category = Stun)
		void Punch();
	UFUNCTION(BlueprintCallable, Category = Stun)
		bool IsStunned();
	UFUNCTION(BlueprintCallable, Category = Power)
		void PowerUp();
protected:

	UFUNCTION(BlueprintCallable, Category = Power)
		void CollectPowerup();

	//UFUNCTION(BlueprintImplementableEvent, Category = Power)
	//	void Addp(float Power);


	/** Function to drop creep and get stunned when punched **/
	UFUNCTION(BlueprintCallable, Category = Stun)
		void Stun();
	
	
};
