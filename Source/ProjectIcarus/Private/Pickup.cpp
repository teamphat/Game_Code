// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_owner(NULL)
{
	//m_ownerID = 0;
	m_pCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = m_pCollider;
	PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(true);

	PickupMesh->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void APickup::Tick(float DeltaSeconds)
{
	
	if (m_bPickedUp)
	{
		//Set our root to the character's root
		SetActorLocation(m_owner->GetActorLocation());
	}
	else
		Super::Tick(DeltaSeconds);
}
void APickup::OnPickedUp_Implementation()
{
	m_bPickedUp = true;
}
void APickup::OnReleased()
{
	m_bPickedUp = false;
	m_owner = NULL;
	
	//now check if we are inside the "altar"
	TArray<AActor*> CollectedActors;
	m_pCollider->GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		AAltar* const Pickup = Cast<AAltar>(CollectedActors[i]);
		if (Pickup)
		{
			Pickup->AddPower();
			Destroy();
		}
	}

}