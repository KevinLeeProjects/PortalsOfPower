// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"

#include "GameClient_CheckIfTutorial.generated.h"

UCLASS()
class PORTALSOFPOWER_API AGameClient_CheckIfTutorial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameClient_CheckIfTutorial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetTutorialCheck(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);
	void TutorialRequestResponse();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
