// Fill out your copyright notice in the Description page of Project Settings.


#include "LowLevel_WizardBullet.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "TutorialLevel_HandleCollision.h"

// Sets default values for this component's properties
ULowLevel_WizardBullet::ULowLevel_WizardBullet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULowLevel_WizardBullet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	lifeTime = 1.0f;
	speed = 500.0f;
	canDestroy = false;

	if (GetOwner())
	{
		GetOwner()->SetLifeSpan(lifeTime);
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &ULowLevel_WizardBullet::OnComponentHit);
		}
	}
}


// Called every frame
void ULowLevel_WizardBullet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (canDestroy)
	{
		GetOwner()->Destroy();
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector ForwardVector = GetOwner()->GetActorForwardVector();
	FVector NewLocation = CurrentLocation + ForwardVector * speed * DeltaTime;
	GetOwner()->SetActorLocation(NewLocation);


}

void ULowLevel_WizardBullet::DestroySelf()
{
	canDestroy = true;
}

void ULowLevel_WizardBullet::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		TutorialLevel_HandleCollision().GetInstance().PlayerTakeDamage(3.0f);
		DestroySelf();
	}
}
