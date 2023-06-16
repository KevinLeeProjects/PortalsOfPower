// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TutorialLevel_SpawnRoomPortal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALSOFPOWER_API UTutorialLevel_SpawnRoomPortal : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialLevel_SpawnRoomPortal();

	void SetVisible();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewSpawnPoint")
	AActor* newSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewSpawnPoint")
	AActor* newGuideSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewSpawnPoint")
	AActor* guide;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
