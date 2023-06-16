// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TutorialLevel_BPTracker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALSOFPOWER_API UTutorialLevel_BPTracker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialLevel_BPTracker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Player")
	AActor* player;

	UPROPERTY(EditAnywhere, Category = "SpawnMacaroni")
	UClass* macaroniBP;

	UPROPERTY(EditAnywhere, Category = "LevelOneFork")
	UClass* levelOneForkBP;

	UPROPERTY(EditAnywhere, Category = "PassiveRing")
	AActor* passiveRing;

	UPROPERTY(EditAnywhere, Category = "AbilityOne")
	AActor* abilityOne;

	UPROPERTY(EditAnywhere, Category = "Ult")
	UClass* ult;

	UPROPERTY(EditAnywhere, Category = "WizardAttack")
	UClass* wizardAttack;

};
