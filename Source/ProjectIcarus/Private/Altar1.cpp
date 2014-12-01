// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "Altar1.h"


AAltar1::AAltar1(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	powerupActive = true;

	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	RootComponent = BaseCollisionComponent;

	AltarMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("AltarMesh"));

	AltarMesh->SetSimulatePhysics(true);

	AltarMesh->AttachTo(RootComponent);
}

void AAltar1::OnAltar_Implementation()
{

}


