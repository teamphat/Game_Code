// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_owner(NULL),
	m_bPickedUp(false)
{
	//m_ownerID = 0;
	m_pCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = m_pCollider;
	m_pCollider->SetSimulatePhysics(true);
	PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(false);

	PickupMesh->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void APickup::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (m_bPickedUp==true)
	{
		//Set our root to the character's root
		FVector newLoc(this->GetActorLocation().X, m_owner->GetActorLocation().Y, m_owner->GetActorLocation().Z + 10);
		
		this->SetActorLocation(newLoc);
	}

	if (this->GetActorLocation().X <= 1000 || this->GetActorLocation().X >= 1450)
		Destroy();
}
void APickup::OnPickedUp_Implementation()
{
	m_bPickedUp = true;
	m_pCollider->SetSimulatePhysics(false);
	//RootComponent->AttachTo(m_owner->GetRootComponent());
}
void APickup::OnReleased()
{
	m_bPickedUp = false;
	m_pCollider->SetSimulatePhysics(true);
	//Because m_owner will be the check to see if we should die in the altar.
	//m_owner = NULL;
	//RootComponent->DetachFromParent(true);
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