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
#include "GameFramework/HUD.h"
#include "TutorialLevel_TutorialHUD.h"
#include "Components/CapsuleComponent.h"

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
