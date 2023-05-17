// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagicMacaroni_Tutorial.h"
#include "TutorialLevel_TutorialHUD.h"
#include "TutorialLevel_TutorialGuide.h"
#include "LowLevel_WizardHP.h"
#include "TutorialLevel_ForkComponent.h"
#include "LowLevel_Wizard.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PORTALSOFPOWER_API TutorialLevel_HandleCollision
{
public:
	TutorialLevel_HandleCollision();
	~TutorialLevel_HandleCollision();

	static TutorialLevel_HandleCollision& GetInstance();

	bool tutorialInitMove;
	void CollisionResponse(const FString& colliderName, AActor* collider);

	void ForkDamage(AActor* collider, UTutorialLevel_ForkComponent* thisFork);

	void SetTutorialHUD(UTutorialLevel_TutorialHUD* Widget);

	void SetGuide(ATutorialLevel_TutorialGuide* tutorialGuide);

	void SetWizardHPHUD(ULowLevel_WizardHP* wizardWidget, float health);

	void SetWizard(ULowLevel_Wizard* wizzy);

	ULowLevel_Wizard* GetWizard();

	void WizardDeath();

	void HandleWizardInteraction();

	void SetMacaroni(UMagicMacaroni_Tutorial* mac);

	UMagicMacaroni_Tutorial* GetMacaroni();

private: 
	UTutorialLevel_TutorialHUD* tutorialHUD;

	ATutorialLevel_TutorialGuide* guide;

	ULowLevel_WizardHP* wizardHP;

	ULowLevel_Wizard* wizard;

	UMagicMacaroni_Tutorial* macaroni;
};
