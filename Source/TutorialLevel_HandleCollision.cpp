// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialLevel_HandleCollision.h"
#include "TutorialLevel_TutorialHUD.h"
#include "GlobalVariables.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


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
	tutorialHUD = Widget;
}

void TutorialLevel_HandleCollision::SetGuide(ATutorialLevel_TutorialGuide* tutorialGuide)
{
	guide = tutorialGuide;
}

void TutorialLevel_HandleCollision::collisionResponse(const FString& colliderName, AActor* collider)
{
	if (colliderName == "SpawnRoomTrigger")
	{
		tutorialInitMove = false;
		GlobalVariables().GetInstance().SetTutorialInitMove(tutorialInitMove);
		if (tutorialHUD)
		{
			UBoxComponent* Collider = collider->FindComponentByClass<UBoxComponent>();
			// Disable the collider component
			if (Collider)
			{
				Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				guide->Move(FVector(1.0f, 0.0f, 0.0f), 1800.0f, 0);
				tutorialHUD->SetText("Hello! My name is Jurgen and I'll be your guide. Follow me!");
			}
		}
	}
}
