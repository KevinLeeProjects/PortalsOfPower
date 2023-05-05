// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialCharacter.h"
#include "GlobalVariables.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/InputSettings.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMath.h"
#include "TutorialLevel_Fork.h"
#include "Components/BoxComponent.h"

bool isJumping;
UBoxComponent* BoxComponent;
// Sets default values
ATutorialLevel_TutorialCharacter::ATutorialLevel_TutorialCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isJumping = false;
	//UE5 has a default player, so doing this sets the player we create to the default
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	USpringArmComponent* springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	springArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	springArm->SetupAttachment(GetMesh());
	springArm->TargetArmLength = 300.f;
	springArm->bUsePawnControlRotation = true;

	mainCamera = CreateDefaultSubobject<UCameraComponent>("mainCamera");
	mainCamera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	mainCamera->bUsePawnControlRotation = false;

	attack = 5;
	firingFrequency = 0.6;
	pace = 5;
	resilience = 5;
	health = 100;
	healthRegen = 4;
	luck = FMath::RandRange(1, 5);
}

// Called when the game starts or when spawned
void ATutorialLevel_TutorialCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (myPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}
	else
	{
		// Get a reference to the current game world
		UWorld* World = GetWorld();

		FVector SpawnLocation = myPlayer->GetActorLocation() + FVector(0, 0, 100);
		FRotator SpawnRotation = myPlayer->GetActorRotation();

		canBasickAttack = false;
		// Set a default player
		myPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

// Called every frame
void ATutorialLevel_TutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationCode();

	if (GlobalVariables().GetInstance().GetTutorialInitMove())
	{
		MovementCode();
		Jump();
		BasicAttack();
	}
}

void ATutorialLevel_TutorialCharacter::MovementCode()
{
	// Check if "W" key is pressed
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::W))
	{
		// Get the character's forward vector
		FVector ForwardVector = GetActorForwardVector();

		// Move the character forward
		AddMovementInput(ForwardVector, 10);
	}
	// Check if "A" key is pressed
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::A))
	{
		// Get the character's right vector
		FVector RightVector = GetActorRightVector();

		// Move the character left
		AddMovementInput(-RightVector, 10);
	}
	// Check if "S" key is pressed
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::S))
	{
		// Get the character's forward vector
		FVector ForwardVector = GetActorForwardVector();

		// Move the character backwards
		AddMovementInput(-ForwardVector, 10);
	}
	// Check if "D" key is pressed
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::D))
	{
		// Get the character's right vector
		FVector RightVector = GetActorRightVector();

		// Move the character right
		AddMovementInput(RightVector, 10);
	}
}

void ATutorialLevel_TutorialCharacter::RotationCode()
{
	// Get the mouse movement
	float DeltaX, DeltaY;
	GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(DeltaX, DeltaY);

	// Calculate the rotation rate
	float RotationRate = 0.1f;

	// Add the rotation input to the controller
	AddControllerYawInput(DeltaX * RotationRate);
	AddControllerPitchInput(-DeltaY * RotationRate);

	// Rotate the SpringArm to match the character's rotation
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();
	if (SpringArm)
	{
		SpringArm->SetRelativeRotation(GetControlRotation() - GetActorRotation());
	}
}

void ATutorialLevel_TutorialCharacter::BasicAttack()
{
	// Check if the left mouse button is pressed and not on cooldown
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton) && !canBasickAttack)
	{
		// Spawn the projectile
		/*FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
		FRotator SpawnRotation = GetActorRotation();*/
		//ATutorialLevel_Fork* fork = GetWorld()->SpawnActor<ATutorialLevel_Fork>(forkBP, SpawnLocation, SpawnRotation);
		AActor* fork = GetWorld()->SpawnActor<AActor>(forkBP, forkSpawnPoint->GetActorLocation() + GetActorForwardVector() * 110.0f, GetActorRotation());
		FVector Scale(0.09f, 0.09f, 0.09f);
		fork->SetActorScale3D(Scale);
		// If the projectile is valid, set its owner
		if (fork)
		{
			fork->SetOwner(this);
		}
		// Set the flag to true to start the cooldown
		canBasickAttack = true;

		// Delay for firingFrequency seconds before resetting the flag
		GetWorld()->GetTimerManager().SetTimer(LeftMouseButtonCooldownTimer, [this]() {
			canBasickAttack = false;
			}, firingFrequency, false);
	}
}

void ATutorialLevel_TutorialCharacter::Jump()
{
	// Check if the character can jump
	if (!isJumping && GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::SpaceBar) && GetCharacterMovement()->IsMovingOnGround())
	{
		// Set the jumping flag
		isJumping = true;
		
		FVector JumpVelocity = FVector(0.f, 0.f, 375.f);
		LaunchCharacter(JumpVelocity, true, true);
	}
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		isJumping = false;
	}
}

// Called to bind functionality to input
void ATutorialLevel_TutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
