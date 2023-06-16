// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LowLevel_WizardAttack.h"
#include "Components/ActorComponent.h"
#include "LowLevel_WizardRadius.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALSOFPOWER_API ULowLevel_WizardRadius : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULowLevel_WizardRadius();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ULowLevel_WizardAttack* wizard;

	bool canMove;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWiz(ULowLevel_WizardAttack* wiz);
	ULowLevel_WizardAttack* GetWiz();

	bool GetCanMove();
};
