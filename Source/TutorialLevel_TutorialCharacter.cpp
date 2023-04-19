// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/InputSettings.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ATutorialLevel_TutorialCharacter::ATutorialLevel_TutorialCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL"));
		// Get a reference to the current game world
		UWorld* World = GetWorld();

		FVector SpawnLocation = myPlayer->GetActorLocation() + FVector(0, 0, 100);
		FRotator SpawnRotation = myPlayer->GetActorRotation();
		// Set a default player
		myPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
		//myPlayer = World->SpawnActor<ATutorialLevel_TutorialCharacter>(ATutorialLevel_TutorialCharacter::StaticClass(), SpawnLocation, SpawnRotation);
	}
}

// Called every frame
void ATutorialLevel_TutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementCode();
	RotationCode();
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

// Called to bind functionality to input
void ATutorialLevel_TutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
