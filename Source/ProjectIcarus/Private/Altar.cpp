// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "Altar.h"


AAltar::AAltar(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	m_pCollider = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("AltarCollider"));
	RootComponent = m_pCollider;
	AltarMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("AltarMesh"));
	AltarMesh->SetSimulatePhysics(true);

	AltarMesh->AttachTo(RootComponent);
}

void AAltar::AddPower()
{
}
void AAltar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}