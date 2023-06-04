// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_Ult.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UTutorialLevel_Ult::UTutorialLevel_Ult()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorialLevel_Ult::BeginPlay()
{
	Super::BeginPlay();

	lifetime = 1.0f;

	GetOwner()->SetLifeSpan(lifetime);
	// ...
	if (GetOwner())
	{
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_Ult::OnComponentHit);

		}
	}
}


// Called every frame
void UTutorialLevel_Ult::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialLevel_Ult::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{

	}
}

