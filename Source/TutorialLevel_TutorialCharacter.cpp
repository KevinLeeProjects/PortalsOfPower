// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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

	mainCamera = CreateDefaultSubobject<UCameraComponent>("mainCamera");
	mainCamera->SetupAttachment(springArm);

	//UCapsuleComponent* capsuleComponent = myPlayer->FindComponentByClass<UCapsuleComponent>();
}

// Called when the game starts or when spawned
void ATutorialLevel_TutorialCharacter::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Warning, TEXT("J"));

	// Enable input for the character
	SetActorTickEnabled(true);

	// Spawn the player's camera
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->SetViewTarget(this);
	}
}

// Called every frame
void ATutorialLevel_TutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FVector MoveDirection = FVector(GetInputAxisValue("MoveForward"), GetInputAxisValue("MoveRight"), 0.f).GetSafeNormal();
	AddMovementInput(MoveDirection, 100 * DeltaTime);*/
	// Move the character forward at a constant rate
	//AddMovementInput(GetActorForwardVector(), 1.f);

	if (myPlayer != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("K"));
		FVector MovementDirection = FVector(1.0f, 0.0f, 0.0f);
		float MovementSpeed = 100.0f;
		FVector Movement = MovementDirection * MovementSpeed * DeltaTime;

		myPlayer->AddActorWorldOffset(Movement, true);
	}
}

// Called to bind functionality to input
void ATutorialLevel_TutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
