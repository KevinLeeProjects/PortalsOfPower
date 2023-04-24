// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_lCharCollision.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GlobalVariables.h"
#include "TutorialLevel_HandleCollision.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTutorialLevel_lCharCollision::UTutorialLevel_lCharCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (GetOwner())
	{
		UCapsuleComponent* capComp = GetOwner()->FindComponentByClass<UCapsuleComponent>();
		if (capComp)
		{
			GetOwner()->SetRootComponent(capComp);
			capComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			capComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_lCharCollision::OnComponentHit);
		}
	}
}

// Called when the game starts
void UTutorialLevel_lCharCollision::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTutorialLevel_lCharCollision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTutorialLevel_lCharCollision::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetActorLabel());
	TutorialLevel_HandleCollision().GetInstance().collisionResponse(OtherActor->GetActorLabel(), OtherActor);
}