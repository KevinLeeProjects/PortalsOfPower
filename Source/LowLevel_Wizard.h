// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LowLevel_Wizard.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALSOFPOWER_API ULowLevel_Wizard : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULowLevel_Wizard();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "SpawnMacaroni")
	UClass* macaroniBP;

	void SpawnMacaroni();

};
