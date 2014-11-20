// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProjectIcarus.h"
#include "ProjectIcarusGameMode.h"
#include "ProjectIcarusCharacter.h"

AProjectIcarusGameMode::AProjectIcarusGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
