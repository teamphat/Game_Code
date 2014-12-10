// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_owner(NULL),
	m_bPickedUp(false)
{
	//m_ownerID = 0;
	
	
	PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(false);
	RootComponent = PickupMesh;
	m_pCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	m_pCollider->AttachTo(RootComponent);
	m_pCollider->SetSimulatePhysics(true);
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<USoundWave> pickup;
		ConstructorHelpers::FObjectFinder<USoundWave> sacrifice;

		FConstructorStatics()
			: pickup(TEXT("USoundWave'/Game/Audio/Pick_Up'"))
			, sacrifice(TEXT("USoundWave'/Game/Audio/Demonic_laugh'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	m_pickupSound = ConstructorStatics.pickup.Object;
	m_sacrificeSound = ConstructorStatics.sacrifice.Object;
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
	UGameplayStatics::PlaySoundAttached(m_pickupSound, GetRootComponent());
}
bool APickup::IsPickedUp() const
{
	return m_bPickedUp;
}

bool APickup::Sacrifice(AActor* i_pAltar)
{
	m_bDropped = true;
	m_bPickedUp = false;
	m_pCollider->SetSimulatePhysics(true);
	m_bStunDrop = false;
	TArray<AActor*> CollectedActors;
	PickupMesh->GetOverlappingActors(CollectedActors);

	FVector pos = GetActorLocation();
	FVector altarPos = i_pAltar->GetActorLocation();
	if (FMath::Abs(FMath::Abs(pos.Y) - FMath::Abs(altarPos.Y)) < 100)
	{
		UGameplayStatics::PlaySoundAttached(m_sacrificeSound, GetRootComponent());
		bRespawn = true;
		return true;
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