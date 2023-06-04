// Fill out your copyright notice in the Description page of Project Settings.

#include "LowLevel_WizardHP.h"
#include "TutorialLevel_HandleCollision.h"
#include "MagicMacaroni_Tutorial.h"
#include "LowLevel_Wizard.h"
#include "Engine/World.h"


void ULowLevel_WizardHP::NativeConstruct()
{
	/*health = 50;
	maxHealth = 50;
	float healthPercent = health / maxHealth;
	resilience = 0;
	healthProgressBar->SetPercent(healthPercent);
	TutorialLevel_HandleCollision().GetInstance().SetWizardHPHUD(this, health);*/
}

//void ULowLevel_WizardHP::SetWizard(ULowLevel_Wizard* wizzy)
//{
//	wizard = wizzy;
//}

void ULowLevel_WizardHP::UpdateHealth(float damage)
{
	/*health -= (damage - resilience);
	float healthPercent = health / maxHealth;
	healthProgressBar->SetPercent(healthPercent);

	if (health <= 0)
	{
		TutorialLevel_HandleCollision().GetInstance().WizardDeath();
		TutorialLevel_HandleCollision().GetInstance().GetWizard()->SpawnMacaroni();
	}*/
}