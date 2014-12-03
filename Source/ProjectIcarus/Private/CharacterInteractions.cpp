// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "CharacterInteractions.h"
#include "PowerupPickup.h"

ACharacterInteractions::ACharacterInteractions(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_pCurrentCarry(NULL),
	m_StunDuration(.5f),
	m_stunTime(0),
	m_bIsStunned(false),
	m_bIsPoweredUp(false)
{
	//Collection Sphere initalization
	PrimaryActorTick.bCanEverTick = true;
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
			if (Pickup && !Pickup->IsPendingKill() && !Pickup->IsPickedUp())
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
	if (!m_bIsStunned)
	{
		//Punches the character in front, causing them to drop their current creep
		/*TArray<AActor*> CollectedActors;
		m_pCollectionRadius->GetOverlappingActors(CollectedActors);

		for (int32 i = 0; i < CollectedActors.Num(); ++i)
		{
			AAltar* const Pickup = Cast<AAltar>(CollectedActors[i]);
			if (Pickup)
			{
				if (m_pCurrentCarry)
				{
					m_pCurrentCarry->Destroy();
					PowerUp();
					m_pCurrentCarry = NULL;
					return;
				}
			}
		}
		m_pCurrentCarry->Drop();*/

		if(m_pCurrentCarry->Sacrifice(m_pAltar))
			PowerUp();
	}
	else
		m_pCurrentCarry->Drop();
	m_pCurrentCarry = NULL;
}
void ACharacterInteractions::SetAltar(AActor* i_pAltar)
{
	m_pAltar = i_pAltar;
}
void ACharacterInteractions::Punch()
{
	//Punches the character in front, causing them to drop their current creep
	TArray<AActor*> CollectedActors;
	m_pCollectionRadius->GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		ACharacterInteractions* const Pickup = Cast<ACharacterInteractions>(CollectedActors[i]);
		if (Pickup && !Pickup->IsPendingKill())
		{
			if (!m_bIsPoweredUp)
				Pickup->Stun();
			else
				Pickup->Destroy();
		}
	}
	//and stunning them for 1s
}
void ACharacterInteractions::Stun()
{
	//Stuns the character
	m_bIsStunned = true;
	if (m_pCurrentCarry)
		DropCreep();
}
void ACharacterInteractions::Tick(float DeltaSeconds)
{
	if (m_bIsStunned)
	{
		if ((m_stunTime += DeltaSeconds) >= m_StunDuration)
		{
			m_bIsStunned = false;
			m_stunTime = 0;
		}
	}
	if (!m_bIsStunned)
		Super::Tick(DeltaSeconds);
}

bool ACharacterInteractions::IsStunned()
{
	return m_bIsStunned;
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
		//Powerup(power);
	}

}
void ACharacterInteractions::PowerUp()
{
	m_bIsPoweredUp = true;
}

