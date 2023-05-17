// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialLevel_HandleCollision.h"
#include "Components/BoxComponent.h"
#include "MagicMacaroni_Tutorial.h"

// Sets default values for this component's properties
UMagicMacaroni_Tutorial::UMagicMacaroni_Tutorial()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	if (GetOwner())
	{
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			//GetOwner()->SetRootComponent(boxComp);
			//boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UMagicMacaroni_Tutorial::OnComponentHit);
		}
	}
	// ...
}


// Called when the game starts
void UMagicMacaroni_Tutorial::BeginPlay()
{
	Super::BeginPlay();
	
	TutorialLevel_HandleCollision().GetInstance().SetMacaroni(this);
	// ...
	
}


// Called every frame
void UMagicMacaroni_Tutorial::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMagicMacaroni_Tutorial::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I: %s"), *OtherActor->GetActorLabel());
	if (OtherActor->GetActorLabel() == "TutorialLevel_TutorialCharacter5")
	{

	}
}