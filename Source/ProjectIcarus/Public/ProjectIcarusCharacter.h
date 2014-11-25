// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Pickup.h"
#include "ProjectIcarusCharacter.generated.h"

UCLASS(config=Game)
class AProjectIcarusCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Pickup radius for the character **/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<USphereComponent> m_pCollectionRadius;
	
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

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		TSubobjectPtr<class USphereComponent> CollectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		float PowerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		float SpeedFactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		float BaseSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		float BasePower;

	//virtual void Tick(float DeltaSounds) OVERRIDE;

	

protected:

	UFUNCTION(BlueprintCallable, Category = Power)
		void CollectPowerup();

	UFUNCTION(BlueprintImplementableEvent, Category = Power)
	void Powerup(float Power);

	/** Function to pickup a creep **/
	UFUNCTION(BlueprintCallable, Category = Pickup)
		void GrabCreep();

	/** Function to drop a creep if one is picked up **/
	UFUNCTION(BlueprintCallable, Category = Pickup)
		void DropCreep();

	/** Function to attack another player **/
	UFUNCTION(BlueprintCallable, Category = Stun)
		void Punch();

	/** Function to drop creep and get stunned when punched **/
	UFUNCTION(BlueprintCallable, Category = Stun)
		void Stun();
	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

};
