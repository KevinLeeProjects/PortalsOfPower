// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_CubeTest.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTutorialLevel_CubeTest::UTutorialLevel_CubeTest()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorialLevel_CubeTest::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent* boxComponent = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (boxComponent)
	{
		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_CubeTest::OnOverlapBegin);
	}
}

void UTutorialLevel_CubeTest::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


// Called every frame
void UTutorialLevel_CubeTest::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

