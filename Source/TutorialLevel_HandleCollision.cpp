// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalVariables.h"
#include "TutorialLevel_TutorialHUD.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TutorialLevel_HandleCollision.h"

TutorialLevel_HandleCollision::TutorialLevel_HandleCollision()
{
}

TutorialLevel_HandleCollision::~TutorialLevel_HandleCollision()
{
}

TutorialLevel_HandleCollision& TutorialLevel_HandleCollision::GetInstance()
{
	// Static local variable to ensure only one instance is created
	static TutorialLevel_HandleCollision instance;
	return instance;
}

void TutorialLevel_HandleCollision::SetTutorialHUD(UTutorialLevel_TutorialHUD* Widget)
{
	MyUserWidgetReference = Widget;
}

void TutorialLevel_HandleCollision::collisionResponse(const FString& colliderName)
{
	if (colliderName == "SpawnRoomTrigger")
	{
		UE_LOG(LogTemp, Warning, TEXT("Sets TEXT"));
		tutorialInitMove = false;
		GlobalVariables().GetInstance().SetTutorialInitMove(tutorialInitMove);
		//UTutorialLevel_TutorialHUD* MyWidget = Cast<UTutorialLevel_TutorialHUD>(MyUserWidgetReference);
		if (MyUserWidgetReference)
		{
			UE_LOG(LogTemp, Warning, TEXT("Set TEXT"));
			MyUserWidgetReference->SetText("Hello");
		}
	}
}
