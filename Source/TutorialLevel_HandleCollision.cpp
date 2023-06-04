// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialLevel_HandleCollision.h"
#include "TutorialLevel_TutorialHUD.h"
#include "GlobalVariables.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "TutorialLevel_AbilityOne.h"
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

//Part 1

void TutorialLevel_HandleCollision::SetTutorialHUD(UTutorialLevel_TutorialHUD* Widget)
{
	tutorialHUD = Widget;
}

void TutorialLevel_HandleCollision::SetPlayer(AActor* character)
{
	player = character;
}

AActor* TutorialLevel_HandleCollision::GetPlayer()
{
	return player;
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

void TutorialLevel_HandleCollision::SetMacaroniBP(UClass* mac)
{
	macaroniBP = mac;
}

UClass* TutorialLevel_HandleCollision::GetMacaroniBP()
{
	return macaroniBP;
}

void TutorialLevel_HandleCollision::SetLevelOneForkBP(UClass* forkOne)
{
	levelOneForkBP = forkOne;
}

UClass* TutorialLevel_HandleCollision::GetLevelOneForkBP()
{
	return levelOneForkBP;
}

void TutorialLevel_HandleCollision::SetWizard(ULowLevel_Wizard* wizzy)
{
	wizard = wizzy;
}

ULowLevel_Wizard* TutorialLevel_HandleCollision::GetWizard()
{
	return wizard;
}

void TutorialLevel_HandleCollision::SpawnRoomTrigger(AActor* collider)
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

void TutorialLevel_HandleCollision::AttackTutorialTrigger(AActor* collider)
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

void TutorialLevel_HandleCollision::SetSpawnRoomPortal(UTutorialLevel_SpawnRoomPortal* portal)
{
	spawnRoomPortal = portal;
}

UTutorialLevel_SpawnRoomPortal* TutorialLevel_HandleCollision::GetSpawnRoomPortal()
{
	return spawnRoomPortal;
}

//void TutorialLevel_HandleCollision::CollisionResponse(bool isActor, AActor* collider)
//{
//	if (colliderName == "SpawnRoomTrigger")
//	{
//		tutorialInitMove = false;
//		GlobalVariables().GetInstance().SetTutorialInitMove(tutorialInitMove);
//		if (tutorialHUD)
//		{
//			UBoxComponent* Collider = collider->FindComponentByClass<UBoxComponent>();
//			// Disable the collider component
//			if (Collider)
//			{
//				Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//				guide->Move(FVector(1.0f, 0.0f, 0.0f), 1800.0f, 0);
//				tutorialHUD->SetText("Hello! My name is Jurgen and I'll be your guide. Use your mouse to look around and follow me!");
//			}
//		}
//	}
//	if (colliderName == "AttackTutorialTrigger")
//	{
//		tutorialInitMove = false;
//		GlobalVariables().GetInstance().SetTutorialInitMove(tutorialInitMove);
//		UBoxComponent* Collider = collider->FindComponentByClass<UBoxComponent>();
//		// Disable the collider component
//		if (Collider)
//		{
//			Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//			tutorialHUD->SetText("Quick! Hold left click to shoot and kill him!");
//			bool setCheckCanAttack = true;
//			GlobalVariables().GetInstance().SetCheckCanAttack(setCheckCanAttack);
//		}
//	}
//}

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
	/*bool macExplain = true;
	GlobalVariables().GetInstance().SetMacaroniExplanation(macExplain);*/
	tutorialHUD->SetText("You did it! And look! He dropped a magic macaroni! Step over it to collect your loot!");
}

void TutorialLevel_HandleCollision::ShowItem()
{
	tutorialHUD->ShowItem();
	/*bool pickup = true;
	GlobalVariables().GetInstance().SetCanPickUp(pickup);*/
}

void TutorialLevel_HandleCollision::HideItem()
{
	tutorialHUD->HideItem();
	/*bool pickup = false;
	GlobalVariables().GetInstance().SetCanPickUp(pickup);*/
}

void TutorialLevel_HandleCollision::SwitchWeapons()
{
	tutorialHUD->SwitchWeapons();

}

void TutorialLevel_HandleCollision::HideArrow(int arrow)
{
	tutorialHUD->HideArrow(arrow);
}

void TutorialLevel_HandleCollision::ExplainMacaroni()
{
	if (GlobalVariables().GetInstance().GetWeaponExplanation())
	{
		tutorialHUD->ShowArrow(0);
		tutorialHUD->SetText("This is your current weapon. It is a 0 star weapon.                                           ");

		bool weaponExplain = false;
		GlobalVariables().GetInstance().SetWeaponExplanation(weaponExplain);

		bool macExplain = true;
		GlobalVariables().GetInstance().SetWeaponStarExplanation(macExplain);
	}
}

void TutorialLevel_HandleCollision::DestroyMacaroni()
{
	macaroni->GetOwner()->Destroy();
}


//part 2

void TutorialLevel_HandleCollision::IntroducePortals()
{
	tutorialHUD->IntroducePortals();
}

void TutorialLevel_HandleCollision::PlayerTakeDamage(float damage)
{
	float currentHealth = tutorialHUD->Health->GetPercent();
	tutorialHUD->Health->SetPercent(currentHealth - (damage / 100));
	UpdatePlayerHealth();
}

void TutorialLevel_HandleCollision::PlayerHeal(float healAmount)
{
	float currentHealth = tutorialHUD->Health->GetPercent();
	float newHealth = currentHealth + (healAmount / 100);
	if (newHealth < 1)
	{
		tutorialHUD->Health->SetPercent(newHealth);
		UpdatePlayerHealth();
	}
}

void TutorialLevel_HandleCollision::UpdatePlayerHealth()
{
	float currentHealth = tutorialHUD->Health->GetPercent() * 100;
	FText healthText = FText::AsNumber(currentHealth);
	FText FullText = FText::Format(FText::FromString("{0}/100"), healthText);
	tutorialHUD->HealthText->SetText(FullText);
}

void TutorialLevel_HandleCollision::SetPassiveRing(AActor* ring)
{
	passiveRing = ring;
}

void TutorialLevel_HandleCollision::SetPassiveRingVisibility(bool visible)
{
	passiveRing->SetActorHiddenInGame(!visible); 
}

void TutorialLevel_HandleCollision::SetAbilityOne(AActor* ability)
{
	abilityOne = ability;
}

AActor* TutorialLevel_HandleCollision::GetAbilityOne()
{
	return abilityOne;
}

void TutorialLevel_HandleCollision::SetAbilityOneVisibility(bool visible)
{
	abilityOne->SetActorHiddenInGame(!visible);
	if (visible)
	{
		tutorialHUD->HideArrow(4);
		FVector targetScale = FVector(10.0f, 10.0f, 1.0f);

		UTutorialLevel_AbilityOne* abilityOneScript = GetAbilityOne()->FindComponentByClass<UTutorialLevel_AbilityOne>();
		abilityOneScript->SetAbilityHidden();
		GetAbilityOne()->SetActorScale3D(targetScale);
		tutorialHUD->AbilityOneCooldownStart();
	}
}

void TutorialLevel_HandleCollision::IntroduceUlt()
{
	bool ultExplain = true;
	GlobalVariables().GetInstance().SetUltExplanationIntro(ultExplain);
	tutorialHUD->SetText("And now finally, let's talk about your ultimate ability. This specific ability is your strongest ability, and therefore has a longer cooldown.                   ");
}

void TutorialLevel_HandleCollision::SetUlt(UClass* ultimate)
{
	ult = ultimate;
}

UClass* TutorialLevel_HandleCollision::GetUlt()
{
	return ult;
}

void TutorialLevel_HandleCollision::UseUlt()
{
	tutorialHUD->UltCooldownStart();
}

void TutorialLevel_HandleCollision::SetWizardAttack(UClass* wiz)
{
	wizardAttack = wiz;
}

UClass* TutorialLevel_HandleCollision::GetWizardAttack()
{
	return wizardAttack;
}