// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagicMacaroni_Tutorial.h"
#include "TutorialLevel_TutorialHUD.h"
#include "TutorialLevel_TutorialGuide.h"
#include "LowLevel_WizardHP.h"
#include "TutorialLevel_ForkComponent.h"
#include "LowLevel_Wizard.h"
#include "TutorialLevel_SpawnRoomPortal.h"
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

	//Part 1

	bool tutorialInitMove;
	//void CollisionResponse(bool isActor, AActor* collider);
	void SpawnRoomTrigger(AActor* collider);

	void SetPlayer(AActor* character);
	AActor* GetPlayer();

	void AttackTutorialTrigger(AActor* collider);

	void ForkDamage(AActor* collider, UTutorialLevel_ForkComponent* thisFork);

	void SetTutorialHUD(UTutorialLevel_TutorialHUD* Widget);

	void SetGuide(ATutorialLevel_TutorialGuide* tutorialGuide);

	void SetSpawnRoomPortal(UTutorialLevel_SpawnRoomPortal* portal);

	UTutorialLevel_SpawnRoomPortal* GetSpawnRoomPortal();

	void SetWizardHPHUD(ULowLevel_WizardHP* wizardWidget, float health);

	void SetWizard(ULowLevel_Wizard* wizzy);

	ULowLevel_Wizard* GetWizard();

	void WizardDeath();

	void HandleWizardInteraction();

	void DestroyMacaroni();

	void ExplainPassive();

	void ExplainQ();

	void ExplainE();

	void ExplainUlt();

	void SetMacaroni(UMagicMacaroni_Tutorial* mac);

	UMagicMacaroni_Tutorial* GetMacaroni();

	void SetMacaroniBP(UClass* mac);

	UClass* GetMacaroniBP();

	void ShowItem();

	void HideItem();

	void SwitchWeapons();

	void HideArrow(int arrow);

	void ExplainMacaroni();

	void SetLevelOneForkBP(UClass* forkOne);

	UClass* GetLevelOneForkBP();



	//Part 2

	void IntroducePortals();

	void PlayerTakeDamage(float damage);

	void PlayerHeal(float healAmount);

	void SetPassiveRing(AActor* ring);

	void SetPassiveRingVisibility(bool visible);

	void UpdatePlayerHealth();

	void SetAbilityOne(AActor* ability);

	AActor* GetAbilityOne();

	void SetAbilityOneVisibility(bool visible);

	void IntroduceUlt();

	void SetUlt(UClass* ultimate);

	UClass* GetUlt();

	void UseUlt();

	void SetWizardAttack(UClass* wiz);
	UClass* GetWizardAttack();

private: 

	//Part 1

	UTutorialLevel_TutorialHUD* tutorialHUD;

	AActor* player;

	ATutorialLevel_TutorialGuide* guide;

	ULowLevel_WizardHP* wizardHP;

	ULowLevel_Wizard* wizard;

	UMagicMacaroni_Tutorial* macaroni;

	UClass* macaroniBP;

	UClass* levelOneForkBP;

	UTutorialLevel_SpawnRoomPortal* spawnRoomPortal;

	//Part 2

	AActor* passiveRing;

	AActor* abilityOne;

	UClass* ult;

	UClass* wizardAttack;
};
