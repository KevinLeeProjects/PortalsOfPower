// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LowLevel_WizardBullet.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALSOFPOWER_API ULowLevel_WizardBullet : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULowLevel_WizardBullet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float lifeTime;
	float speed;
	float canDestroy;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	void DestroySelf();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
