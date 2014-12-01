// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectIcarus.h"
#include "PowerupPickup.h"


APowerupPickup::APowerupPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PowerLevel = 150.f;
}

void APowerupPickup :: OnAltar_Implementation()
{
	Super::OnAltar_Implementation();

	Destroy();

}

