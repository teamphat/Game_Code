// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProjectIcarus.h"
#include "ProjectIcarusCharacter.h"
#include "PowerupPickup.h"

AProjectIcarusCharacter::AProjectIcarusCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP),
	m_pCurrentCarry(NULL),
	m_StunDuration(1.f),
	m_stunTime(0),
	m_bIsStunned(false)
{
	//Collection Sphere initalization
	
	m_pCollectionRadius = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	m_pCollectionRadius->AttachTo(RootComponent);

	PowerLevel = 2000.f;
	SpeedFactor = 0.75;
	BaseSpeed = 10.0f;
	
CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere2"));
 CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Face in the direction we are moving..
	CharacterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->GravityScale = 2.f;
	CharacterMovement->AirControl = 0.80f;
	CharacterMovement->JumpZVelocity = 1000.f;
	CharacterMovement->GroundFriction = 3.f;
	CharacterMovement->MaxWalkSpeed = 600.f;
	CharacterMovement->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectIcarusCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings

	InputComponent->BindAction("Pickup", IE_Pressed, this, &AProjectIcarusCharacter::GrabCreep);
	InputComponent->BindAction("Punch", IE_Pressed, this, &AProjectIcarusCharacter::Punch);
	InputComponent->BindAction("Pickup", IE_Pressed, this, &AProjectIcarusCharacter::CollectPowerup);
	//Movement and jumping
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AProjectIcarusCharacter::MoveRight);
	InputComponent->BindTouch(IE_Pressed, this, &AProjectIcarusCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AProjectIcarusCharacter::TouchStopped);
}

void AProjectIcarusCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AProjectIcarusCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AProjectIcarusCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AProjectIcarusCharacter::GrabCreep()
{
	if (!m_pCurrentCarry)
	{
		TArray<AActor*> CollectedActors;
		m_pCollectionRadius->GetOverlappingActors(CollectedActors);

		for (int32 i = 0; i < CollectedActors.Num(); ++i)
		{
			APickup* const Pickup = Cast<APickup>(CollectedActors[i]);
			if (Pickup && !Pickup->IsPendingKill())
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
void AProjectIcarusCharacter::DropCreep()
{
	//Drop the currently carried creep
	
	//if it is dropped on the altar sacrifice it

	//set our pointer to null
	m_pCurrentCarry->OnReleased();
	m_pCurrentCarry = NULL;
}
void AProjectIcarusCharacter::Punch()
{
	//Punches the character in front, causing them to drop their current creep
	//and stunning them for 1s
}
void AProjectIcarusCharacter::Stun()
{
	//Stuns the character
	m_bIsStunned = true;
}
void AProjectIcarusCharacter::Tick(float DeltaSeconds)
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

	CharacterMovement->MaxWalkSpeed = SpeedFactor * PowerLevel + BaseSpeed;
}


void AProjectIcarusCharacter::CollectPowerup()
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
		Powerup(power);
	}

}