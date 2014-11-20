// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_ownerID(0)
{
	//m_ownerID = 0;
	m_pCollider = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = m_pCollider;
}


void APickup::OnPickedUp_Implementation()
{
	//no default behavior as pickups are random
}