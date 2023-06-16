// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_AbilityRoomPortal.h"
#include "Components/BoxComponent.h"
#include "TutorialLevel_HandleCollision.h"

// Sets default values for this component's properties
UTutorialLevel_AbilityRoomPortal::UTutorialLevel_AbilityRoomPortal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorialLevel_AbilityRoomPortal::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwner())
	{
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			//GetOwner()->SetRootComponent(boxComp);
			boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_AbilityRoomPortal::OnComponentHit);

			//TutorialLevel_HandleCollision().GetInstance().SetSpawnRoomPortal(this);
		}
	}
}


// Called every frame
void UTutorialLevel_AbilityRoomPortal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialLevel_AbilityRoomPortal::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		OtherActor->SetActorLocation(newSpawnPoint->GetActorLocation());
		guide->SetActorLocation(newGuideSpawnPoint->GetActorLocation());
		TutorialLevel_HandleCollision().GetInstance().IntroduceUlt();
	}
}