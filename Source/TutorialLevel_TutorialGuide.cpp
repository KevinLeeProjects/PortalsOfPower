// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialGuide.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "GlobalVariables.h"
#include "TutorialLevel_HandleCollision.h"
#include "GameFramework/HUD.h"
#include "TutorialLevel_TutorialHUD.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATutorialLevel_TutorialGuide::ATutorialLevel_TutorialGuide()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tutorialGuide_isJumping = false;
	TimerHandle.Invalidate();

	// Set up the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	// Set up the movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->MaxSpeed = 500.f; // Set the maximum speed of the movement component

	TutorialLevel_HandleCollision().GetInstance().SetGuide(this);
}

// Called when the game starts or when spawned
void ATutorialLevel_TutorialGuide::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	FString welcomeMessage = "Hello";

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), UTutorialLevel_TutorialHUD::StaticClass());

	UTutorialLevel_TutorialHUD* TutorialHUDInstance = Cast<UTutorialLevel_TutorialHUD>(Widget);
	if (Widget)
	{
		TutorialHUDInstance = Cast<UTutorialLevel_TutorialHUD>(Widget);
		//TutorialHUDInstance->AddToViewport();
	}

	if (TutorialHUDInstance)
	{
		//TutorialHUDInstance->SetText(welcomeMessage);
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATutorialLevel_TutorialGuide::NextJump, 1.0f, true);
}

// Called every frame
void ATutorialLevel_TutorialGuide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATutorialLevel_TutorialGuide::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATutorialLevel_TutorialGuide::Jump()
{
	// Check if the character can jump
	if (!tutorialGuide_isJumping && GetCharacterMovement()->IsMovingOnGround())
	{
		// Set the jumping flag
		tutorialGuide_isJumping = true;

		FVector JumpVelocity = FVector(0.f, 0.f, 100.f);
		LaunchCharacter(JumpVelocity, true, true);
	}
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		tutorialGuide_isJumping = false;
	}
}

void ATutorialLevel_TutorialGuide::NextJump()
{
	// Do whatever you need to do when the timer fires...
	Jump();
}

void ATutorialLevel_TutorialGuide::Move(FVector direction, float distance, float sequence)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	// Divide the total distance into smaller steps
	float StepSize = 1.0f; // Set the size of each step
	int NumSteps = FMath::RoundToInt(distance / StepSize); // Calculate the number of steps based on the total distance and the step size

	// Calculate the total time it should take to complete the movement
	float MovementTime = NumSteps * 0.000003f; // Set the time for each step to 0.1 seconds
	// Start a timer that will update the actor's location every 0.1 seconds
	
	
	GetWorld()->GetTimerManager().SetTimer(movementTimerHandle, [=]() mutable
		{
			static int Step = 0; // Keep track of the current step
			if (Step < NumSteps)
			{
				FVector CurrentLocation = GetActorLocation();
				FVector StepVector = direction * StepSize;
				FVector NewLocation = CurrentLocation + StepVector;
				SetActorLocation(NewLocation);
				bool setTutorialInitMove = false;
				GlobalVariables().GetInstance().SetTutorialInitMove(setTutorialInitMove);
				Step++;
			}
			else
			{
				// Cancel the timer once all steps have been taken
				
				GetWorld()->GetTimerManager().ClearTimer(movementTimerHandle);
				
				if (sequence == 0)
				{
					AActor* wizard = GetWorld()->SpawnActor<AActor>(wizardBP, wizardSpawnPoint->GetActorLocation() + GetActorForwardVector() * 110.0f, GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f));
					/*UBoxComponent* wizardCollider = wizard->FindComponentByClass<UBoxComponent>();
					FVector wizardScale(1.0f, 1.0f, 1.0f);
					wizardCollider->SetBoxExtent(wizardScale);*/
					TutorialLevel_HandleCollision().GetInstance().HandleWizardInteraction();
				}
				Step = 0;
			}
		}, MovementTime, true);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATutorialLevel_TutorialGuide::NextJump, 1.0f, true);
}
