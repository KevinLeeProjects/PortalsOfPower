// Fill out your copyright notice in the Description page of Project Settings.


#include "Server_Character.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AServer_Character::AServer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AServer_Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		// Initialize the target location on the server
		TargetLocation = GetActorLocation();
	}
}

// Called every frame
void AServer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		// Update the actor's location on the server
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 10.0f));
	}
}

// Called to bind functionality to input
//void AServer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void AServer_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the TargetLocation property
	DOREPLIFETIME_CONDITION(AServer_Character, TargetLocation, COND_OwnerOnly);
}

void AServer_Character::Server_UpdateTargetLocation_Implementation(const FVector& NewLocation)
{
	// Update the target location on the server
	TargetLocation = NewLocation;
}

bool AServer_Character::Server_UpdateTargetLocation_Validate(const FVector& NewLocation)
{
	// Add validation logic if required
	return true;
}

void AServer_Character::OnRep_TargetLocation()
{
	// Implement your logic when TargetLocation is replicated to clients
}
