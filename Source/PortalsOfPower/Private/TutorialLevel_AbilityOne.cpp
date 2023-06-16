// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_AbilityOne.h"
#include "TutorialLevel_HandleCollision.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GlobalVariables.h"
#include "Components/BoxComponent.h"



// Sets default values for this component's properties
UTutorialLevel_AbilityOne::UTutorialLevel_AbilityOne()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTutorialLevel_AbilityOne::BeginPlay()
{
	Super::BeginPlay();

	abilityLifetime = 1.0f;
	pace = 600.0f;
	tempPace = 1000.0f;
	//
	cooldown = 3.0f;
	// ...
	if (GetOwner())
	{
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_AbilityOne::OnComponentHit);
			
		}
	}
}

void UTutorialLevel_AbilityOne::SetAbilityHidden()
{
	
	GetWorld()->GetTimerManager().SetTimer(abilityOneTimerHandle, [=]() mutable
		{
			GetOwner()->SetActorHiddenInGame(true);
			GetOwner()->SetActorScale3D(FVector(0, 0, 0));
			GlobalVariables().GetInstance().SetPace(pace);
		}, abilityLifetime, false);
}

// Called every frame
void UTutorialLevel_AbilityOne::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialLevel_AbilityOne::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if(OtherActor->ActorHasTag("Player"))
	{ 
		//cooldown = GlobalVariables().GetInstance().GetAbilityOneCooldown();

		GlobalVariables().GetInstance().SetPace(tempPace);

		bool abilityOneActive = false;
		GlobalVariables().GetInstance().SetCanUseAbilityOne(abilityOneActive);

		GetWorld()->GetTimerManager().SetTimer(abilityOneCooldownHandle, [=]() mutable
			{
				bool abilityOneActive = true;
				GlobalVariables().GetInstance().SetCanUseAbilityOne(abilityOneActive);
			}, cooldown, false);
	}
	
}
