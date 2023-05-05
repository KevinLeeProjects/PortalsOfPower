// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "TutorialLevel_Fork.h"

// Sets default values
ATutorialLevel_Fork::ATutorialLevel_Fork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	//GetWorld()->GetTimerManager().SetTimer(LifespanTimerHandle, this, &ATutorialLevel_Fork::DestroyProjectile, lifeTime, false);
}

// Called when the game starts or when spawned
void ATutorialLevel_Fork::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("KIKs: %s"), *GetName());

	if (this->GetRootComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("L"));
	}
	if (this->RootComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("J"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Owner class: %s"), *GetOwner()->GetClass()->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Attached to actor: %s"), *GetAttachParentActor()->GetClass()->GetName());
	if (this->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("K"));
	}

	
	/*if (IsValid(RootComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("YES"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BNOT"));
	}
	lifeTime = 2.0f;
	SetLifeSpan(lifeTime);*/
}

void ATutorialLevel_Fork::DestroyProjectile()
{
	//if (GetOwner())
	//{
	//}
	/*UE_LOG(LogTemp, Warning, TEXT("KIJ"));
	Destroy();*/
	
}

// Called every frame
void ATutorialLevel_Fork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

