// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Server_Character.generated.h"

UCLASS()
class PORTALSOFPOWER_API AServer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AServer_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Server_UpdateTargetLocation_Implementation(const FVector& NewLocation);
	virtual bool Server_UpdateTargetLocation_Validate(const FVector& NewLocation);


	UPROPERTY(ReplicatedUsing = OnRep_TargetLocation)
		FVector TargetLocation;

	UFUNCTION()
		void OnRep_TargetLocation();
};
