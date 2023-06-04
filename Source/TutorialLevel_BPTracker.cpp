// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_BPTracker.h"
#include "TutorialLevel_HandleCollision.h"

// Sets default values for this component's properties
UTutorialLevel_BPTracker::UTutorialLevel_BPTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorialLevel_BPTracker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TutorialLevel_HandleCollision().GetInstance().SetPlayer(player);

	TutorialLevel_HandleCollision().GetInstance().SetMacaroniBP(macaroniBP);

	TutorialLevel_HandleCollision().GetInstance().SetLevelOneForkBP(levelOneForkBP);

	TutorialLevel_HandleCollision().GetInstance().SetPassiveRing(passiveRing);
	TutorialLevel_HandleCollision().GetInstance().SetPassiveRingVisibility(false);

	TutorialLevel_HandleCollision().GetInstance().SetAbilityOne(abilityOne);
	TutorialLevel_HandleCollision().GetInstance().SetAbilityOneVisibility(false);

	TutorialLevel_HandleCollision().GetInstance().SetUlt(ult);

	TutorialLevel_HandleCollision().GetInstance().SetWizardAttack(wizardAttack);
}


// Called every frame
void UTutorialLevel_BPTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

