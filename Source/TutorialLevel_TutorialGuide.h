// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "GameFramework/HUD.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "TutorialLevel_TutorialGuide.generated.h"


UCLASS()
class PORTALSOFPOWER_API ATutorialLevel_TutorialGuide : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutorialLevel_TutorialGuide();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool tutorialGuide_isJumping;
	void Jump();
	FTimerHandle TimerHandle;
	void NextJump();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* MovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
