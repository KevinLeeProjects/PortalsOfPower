// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "LowLevel_WizardAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALSOFPOWER_API ULowLevel_WizardAttack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULowLevel_WizardAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FacePlayer();

	void Move(float deltaTime);

	void Shoot();
	float firingFrequency;
	float canShoot;

	AActor* player;

	bool canMove;

	float movementSpeed;
	float interpolationFactor;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UClass* bullet;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	AActor* bulletSpawnpoint;

	FTimerHandle bulletCooldown;

	//float health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float damage);

	void SetPlayer(AActor* playerActor);

	void SetCanMove(bool& move);
};
