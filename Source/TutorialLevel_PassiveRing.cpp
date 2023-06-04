// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_PassiveRing.h"
#include "TutorialLevel_HandleCollision.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

// Declare a timer handle for scaling
FTimerHandle ScaleTimerHandle;

// The target scale you want to reach
FVector targetScale = FVector(0.0f, 0.0f, 0.0f);

FVector originalScale;

// The time it takes to reach the target scale
float ScaleDuration = 1.0f; // 1 second

// The starting scale of your object
FVector InitialScale;

// The elapsed time for the scaling animation
float ElapsedTime = 0.0f;

// Sets default values for this component's properties
UTutorialLevel_PassiveRing::UTutorialLevel_PassiveRing()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UTutorialLevel_PassiveRing::BeginPlay()
{
	Super::BeginPlay();

	extensionTime = 0.000003f;
	healAmount = 0.5f;

	originalScale = GetOwner()->GetActorScale3D();

	// Store the initial scale
	InitialScale = GetOwner()->GetActorScale3D();

	// Start the scaling timer
	GetWorld()->GetTimerManager().SetTimer(ScaleTimerHandle, this, &UTutorialLevel_PassiveRing::ScaleObject, ScaleDuration, true);
	
	if (GetOwner())
	{
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &UTutorialLevel_PassiveRing::OnComponentHit);

			//GetWorld()->GetTimerManager().SetTimer(PassiveRingTimer, [this]() {
			//	FVector NewScale = GetOwner()->GetActorScale3D() - FVector(0.03f, 0.03f, 0.03f); // Example scale values (2.0f means double the size)
			//	GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);
			//	}, extensionTime, true);
			
		}
	}
	// ...
	
}


void UTutorialLevel_PassiveRing::ScaleObject()
{
	if (GetOwner()->GetActorScale3D() == originalScale)
	{
		GetOwner()->SetActorScale3D(targetScale);
	}
	else
	{
		GetOwner()->SetActorScale3D(originalScale);
	}
	//// Update the elapsed time
	//ElapsedTime += 0.01f;

	//// Calculate the interpolation alpha based on the elapsed time
	//float Alpha = FMath::Clamp(ElapsedTime / ScaleDuration, 0.0f, 1.0f);

	//// Clamp the alpha value between 0 and 1
	//Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);

	//// Apply the interpolation curve for smoother scaling
	//float CurveAlpha = FMath::InterpEaseInOut(0.0f, 1.0f, Alpha, 3.0f);

	//// Interpolate the scale from the initial scale to the target scale
	//FVector NewScale = FMath::Lerp(InitialScale, TargetScale, CurveAlpha);

	//// Apply the new scale to the object
	//GetOwner()->SetActorScale3D(NewScale);

	//// Check if the interpolation is complete
	//if (Alpha >= 1.0f)
	//{
	//	// Scaling is complete, so we can stop the timer
	//	//GetWorld()->GetTimerManager().ClearTimer(ScaleTimerHandle);
	//	if (TargetScale != originalScale)
	//	{
	//		TargetScale = originalScale;
	//		InitialScale = FVector(0.0f, 0.0f, 0.0f);
	//	}
	//	else
	//	{
	//		TargetScale = FVector(0.0f, 0.0f, 0.0f);
	//		InitialScale = originalScale;
	//	}

	//}
}

// Called every frame
void UTutorialLevel_PassiveRing::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialLevel_PassiveRing::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		TutorialLevel_HandleCollision().GetInstance().PlayerHeal(healAmount);
	}
}
