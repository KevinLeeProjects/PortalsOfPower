// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "TutorialLevel_TutorialCharacter.generated.h"

UCLASS()
class PORTALSOFPOWER_API ATutorialLevel_TutorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutorialLevel_TutorialCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* mainCamera; // Camera component

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    AActor* myPlayer; // Player

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	AActor* forkSpawnPoint; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	AActor* ultSpawnPoint;

	void MovementCode();
	void RotationCode();
	void Jump();
	void BasicAttack();
	void PickUp();
	void UpdateHealth();
	void AbilityOne();
	void Ult();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	FTimerHandle LeftMouseButtonCooldownTimer;

	bool canBasickAttack;

	UPROPERTY(EditAnywhere, Category = "SpawnFork")
	UClass* forkBP;

	

private:
	float attack;
	float firingFrequency;
	float pace;
	float resilience;
	float health;
	float maxHealth;
	float healthRegen;
	float luck;

	FTimerHandle ultCooldownTimer;
	float ultCooldown;
};
