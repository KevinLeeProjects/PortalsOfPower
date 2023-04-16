// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClient_CheckIfTutorial.h"
#include "Kismet/GameplayStatics.h"

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"
#include "GlobalVariables.h"

//C++
#include<iostream>
#include<algorithm>

// Sets default values
AGameClient_CheckIfTutorial::AGameClient_CheckIfTutorial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameClient_CheckIfTutorial::BeginPlay()
{
	Super::BeginPlay();
	FString databasePlayerURL = GlobalVariables().GetInstance().GetDBURL() + "/players/" + GlobalVariables().GetInstance().GetUsername() + "/TutorialComplete.json";
	
	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(databasePlayerURL);

	// Set the response callback
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AGameClient_CheckIfTutorial::TutorialRequestResponse);
	// Send the HTTP request
	HttpRequest->ProcessRequest();
}

void AGameClient_CheckIfTutorial::TutorialRequestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
{
	if (Response->GetContentAsString() == "false")
	{
		UWorld* world = GetWorld();

		if (world)
		{
			FString tutorialLevelName = "TutorialLevel";
			UGameplayStatics::OpenLevel(world, FName(*tutorialLevelName));
		}
	}
}
// Called every frame
void AGameClient_CheckIfTutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

