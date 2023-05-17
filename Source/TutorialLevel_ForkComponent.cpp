// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "TutorialLevel_HandleCollision.h"
#include "TutorialLevel_ForkComponent.h"

// Sets default values for this component's properties
UTutorialLevel_ForkComponent::UTutorialLevel_ForkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	lifeTime = 1.0f;
	speed = 1000.0f;
	canDestroy = false;
	// ...
}


// Called when the game starts
void UTutorialLevel_ForkComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		GetOwner()->SetLifeSpan(lifeTime);
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_ForkComponent::OnComponentHit);
		}
	}
}


// Called every frame
void UTutorialLevel_ForkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (canDestroy)
	{
		GetOwner()->Destroy();
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector ForwardVector = GetOwner()->GetActorForwardVector();
	FVector NewLocation = CurrentLocation + ForwardVector * speed * DeltaTime;
	GetOwner()->SetActorLocation(NewLocation);

	
}

void UTutorialLevel_ForkComponent::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->GetActorLabel() != "TutorialLevel_TutorialCharacter5")
	{
		UE_LOG(LogTemp, Warning, TEXT("HI: %s"), *OtherActor->GetActorLabel());
		if (OtherActor->GetActorLabel() == "enemy_wizard0")
		{
			TutorialLevel_HandleCollision().GetInstance().ForkDamage(OtherActor, this);
		}
	}
}

void UTutorialLevel_ForkComponent::DestroySelf()
{
	canDestroy = true;
	//GetOwner()->Destroy();
}

