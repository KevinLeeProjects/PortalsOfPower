// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_SpawnRoomPortal.h"

#include "Components/BoxComponent.h"
#include "TutorialLevel_HandleCollision.h"

// Sets default values for this component's properties
UTutorialLevel_SpawnRoomPortal::UTutorialLevel_SpawnRoomPortal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UTutorialLevel_SpawnRoomPortal::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwner())
	{
		GetOwner()->SetActorHiddenInGame(true);

		// Disable collision for the actor
		GetOwner()->SetActorEnableCollision(false);

		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			//GetOwner()->SetRootComponent(boxComp);
			boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_SpawnRoomPortal::OnComponentHit);

			TutorialLevel_HandleCollision().GetInstance().SetSpawnRoomPortal(this);
		}
	}
}


// Called every frame
void UTutorialLevel_SpawnRoomPortal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialLevel_SpawnRoomPortal::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		OtherActor->SetActorLocation(newSpawnPoint->GetActorLocation());
		guide->SetActorLocation(newGuideSpawnPoint->GetActorLocation());
		TutorialLevel_HandleCollision().GetInstance().IntroducePortals();
	}
}

void UTutorialLevel_SpawnRoomPortal::SetVisible()
{
	GetOwner()->SetActorHiddenInGame(false);

	GetOwner()->SetActorEnableCollision(true);
}
