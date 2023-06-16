// Fill out your copyright notice in the Description page of Project Settings.


#include "LowLevel_WizardAttack.h"
#include "Components/StaticMeshComponent.h"
#include "TutorialLevel_HandleCollision.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "LowLevel_WizardRadius.h"
#include "Engine/World.h"

// Sets default values for this component's properties
ULowLevel_WizardAttack::ULowLevel_WizardAttack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULowLevel_WizardAttack::BeginPlay()
{
	Super::BeginPlay();

	movementSpeed = 80.0f;
	interpolationFactor = 0.5f;

	firingFrequency = 1.0f;
	canShoot = true;

	AActor* ParentActor = GetOwner();
	// Get an array of child actors
	TArray<AActor*> ChildActors;
	ParentActor->GetAttachedActors(ChildActors);

	// Iterate through the child actors
	for (AActor* ChildActor : ChildActors)
	{
		// Do something with each child actor
		// ...
		if (ChildActor->ActorHasTag("WizardRadius"))
		{
			ULowLevel_WizardRadius* wizardRad = ChildActor->FindComponentByClass<ULowLevel_WizardRadius>();
			if (wizardRad)
			{
				wizardRad->SetWiz(this);
			}
		}
		if (ChildActor->ActorHasTag("WizardAttackSpawnPoint"))
		{

		}
	}
}

void ULowLevel_WizardAttack::SetPlayer(AActor* playerActor)
{
	player = playerActor;
}

void ULowLevel_WizardAttack::SetCanMove(bool& move)
{
	canMove = move;
}

// Called every frame
void ULowLevel_WizardAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FacePlayer();
	if (canMove && player != nullptr)
	{
		Move(DeltaTime);
		if (canShoot)
		{
			Shoot();
		}
		
	}
}

void ULowLevel_WizardAttack::FacePlayer()
{
	if (TutorialLevel_HandleCollision().GetInstance().GetPlayer())
	{
		// Get the direction from the enemy component to the player
		FVector Direction = TutorialLevel_HandleCollision().GetInstance().GetPlayer()->GetActorLocation() - GetOwner()->GetActorLocation();
		Direction.Z = 0.0f; // Ensure the enemy only rotates in the XY plane

		// Rotate the enemy component to face the player
		FRotator TargetRotation = Direction.Rotation() + FRotator(0.0f, -90.0f, 0.0f);
		//SetWorldRotation(TargetRotation);
		GetOwner()->SetActorRotation(TargetRotation);
	}
}

void ULowLevel_WizardAttack::TakeDamage(float damage)
{
	UWidgetComponent* WidgetComp = GetOwner()->FindComponentByClass<UWidgetComponent>();
	UClass* testOne = WidgetComp->GetWidgetClass()->GetSuperClass();
	ULowLevel_WizardHP* testTwo = Cast<ULowLevel_WizardHP>(WidgetComp->GetUserWidgetObject());
	UE_LOG(LogTemp, Warning, TEXT("TEST: %s"), *testOne->GetName());

	if (testTwo)
	{
		if (testTwo->healthProgressBar)
		{
			testTwo->UpdateHealth(damage, GetOwner());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DOES NOT EXIST"));

	}
}

void ULowLevel_WizardAttack::Move(float deltaTime)
{
	

	// Calculate the target position
	FVector TargetPosition = player->GetActorLocation();

	// Calculate the movement vector towards the target position
	FVector MovementVector = (TargetPosition - GetOwner()->GetActorLocation()).GetSafeNormal() * movementSpeed * deltaTime;

	// Interpolate the actor's position towards the target position
	FVector NewPosition = FMath::VInterpTo(GetOwner()->GetActorLocation(), TargetPosition, deltaTime, interpolationFactor);

	// Set the new position for the actor
	GetOwner()->SetActorLocation(NewPosition);
}

void ULowLevel_WizardAttack::Shoot()
{
	canShoot = false;
	AActor* wizardBullet = GetWorld()->SpawnActor<AActor>(bullet, bulletSpawnpoint->GetActorLocation(), GetOwner()->GetActorRotation() - FRotator(0.0f, -90.0f, 0.0f));

	// Delay for firingFrequency seconds before resetting the flag
	GetWorld()->GetTimerManager().SetTimer(bulletCooldown, [this]() {
		canShoot = true;
		}, firingFrequency, false);
	
}