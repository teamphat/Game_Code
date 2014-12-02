// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "CharacterInteractions.h"
#include "PowerupPickup.h"

ACharacterInteractions::ACharacterInteractions(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_pCurrentCarry(NULL),
	m_StunDuration(1.f),
	m_stunTime(0),
	m_bIsStunned(false)
{
	//Collection Sphere initalization

	m_pCollectionRadius = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	RootComponent=m_pCollectionRadius;

	PowerLevel = 2000.f;
	SpeedFactor = 0.75;
	BaseSpeed = 10.0f;

	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere2"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(500.f);
	
}

void ACharacterInteractions::GrabCreep()
{
	if (!m_pCurrentCarry)
	{
		TArray<AActor*> CollectedActors;
		m_pCollectionRadius->GetOverlappingActors(CollectedActors);

		for (int32 i = 0; i < CollectedActors.Num(); ++i)
		{
			APickup* const Pickup = Cast<APickup>(CollectedActors[i]);
			if (Pickup && !Pickup->IsPendingKill() && !Pickup->m_owner)
			{
				Pickup->m_owner = this;
				m_pCurrentCarry = Pickup;
				Pickup->OnPickedUp();
				break;
			}
		}
	}
	else
		DropCreep();
}
void ACharacterInteractions::DropCreep()
{
	//Drop the currently carried creep

	//if it is dropped on the altar sacrifice it

	//set our pointer to null
	m_pCurrentCarry->OnReleased();
	m_pCurrentCarry = NULL;
}
void ACharacterInteractions::Punch()
{
	//Punches the character in front, causing them to drop their current creep
	//and stunning them for 1s
}
void ACharacterInteractions::Stun()
{
	//Stuns the character
	m_bIsStunned = true;
}
void ACharacterInteractions::Tick(float DeltaSeconds)
{

}


void ACharacterInteractions::CollectPowerup()
{
	float power = 0.0f;

	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		APowerupPickup* const TestPower = Cast<APowerupPickup>(CollectedActors[iCollected]);

		if (TestPower && !TestPower->IsPendingKill() && TestPower->powerupActive)
		{


			power = power + TestPower->PowerLevel;
			TestPower->OnAltar();
			TestPower->powerupActive = false;

		}
	}

	if (power > 0.f)
	{
		Powerup(power);
	}

}

