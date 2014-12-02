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
bool APickup::IsPickedUp() const
{
	return m_bPickedUp;
}

bool APickup::Sacrifice()
{
	m_bDropped = true;
	m_bPickedUp = false;
	m_pCollider->SetSimulatePhysics(true);
	m_bStunDrop = false;
	TArray<AActor*> CollectedActors;
	PickupMesh->GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		AAltar* const Pickup = Cast<AAltar>(CollectedActors[i]);
		if (Pickup)
		{
			Destroy();
			return true;
		}
	}
	return false;
}

void APickup::Drop()
{
	m_bDropped = true;
	m_bStunDrop = true;
	m_bPickedUp = false;
	m_pCollider->SetSimulatePhysics(true);
}