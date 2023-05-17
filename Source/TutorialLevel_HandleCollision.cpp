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

void TutorialLevel_HandleCollision::SetWizardHPHUD(ULowLevel_WizardHP* wizardWidget, float health)
{
	wizardHP = wizardWidget;
}

void TutorialLevel_HandleCollision::SetMacaroni(UMagicMacaroni_Tutorial* mac)
{
	macaroni = mac;
}

UMagicMacaroni_Tutorial* TutorialLevel_HandleCollision::GetMacaroni()
{
	return macaroni;
}

void TutorialLevel_HandleCollision::SetWizard(ULowLevel_Wizard* wizzy)
{
	wizard = wizzy;
}

ULowLevel_Wizard* TutorialLevel_HandleCollision::GetWizard()
{
	return wizard;
}

void TutorialLevel_HandleCollision::CollisionResponse(const FString& colliderName, AActor* collider)
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
				tutorialHUD->SetText("Hello! My name is Jurgen and I'll be your guide. Use your mouse to look around and follow me!");
			}
		}
	}
	if (colliderName == "AttackTutorialTrigger")
	{
		tutorialInitMove = false;
		GlobalVariables().GetInstance().SetTutorialInitMove(tutorialInitMove);
		UBoxComponent* Collider = collider->FindComponentByClass<UBoxComponent>();
		// Disable the collider component
		if (Collider)
		{
			Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			tutorialHUD->SetText("Quick! Hold left click to shoot and kill him!");
			bool setCheckCanAttack = true;
			GlobalVariables().GetInstance().SetCheckCanAttack(setCheckCanAttack);
		}
	}
}

void TutorialLevel_HandleCollision::HandleWizardInteraction()
{
	if (tutorialHUD)
	{
		tutorialHUD->SetText("AHHHHH!!! A wizard! Help!");
	}
}

void TutorialLevel_HandleCollision::ForkDamage(AActor* collider, UTutorialLevel_ForkComponent* thisFork)
{
	if (wizardHP)
	{
		wizardHP->UpdateHealth(10);
		thisFork->DestroySelf();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WIZARD NULL"));
	}
}

void TutorialLevel_HandleCollision::WizardDeath()
{
	wizard->GetOwner()->Destroy();
	bool macExplain = true;
	GlobalVariables().GetInstance().SetMacaroniExplanation(macExplain);
	tutorialHUD->SetText("You did it! And look! He dropped a magic macaroni! Step over it to collect your loot!           ");
}


