// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "TutorialLevel_Fork.generated.h"

UCLASS()
class PORTALSOFPOWER_API ATutorialLevel_Fork : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialLevel_Fork();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Speed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float lifeTime;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Damage = 10.f;

	// Timer handle for destroying the actor after the specified lifespan
	FTimerHandle LifespanTimerHandle;

	void DestroyProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
