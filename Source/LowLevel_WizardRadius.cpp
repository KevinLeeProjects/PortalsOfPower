// Fill out your copyright notice in the Description page of Project Settings.


#include "LowLevel_WizardRadius.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
ULowLevel_WizardRadius::ULowLevel_WizardRadius()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULowLevel_WizardRadius::BeginPlay()
{
	Super::BeginPlay();

	canMove = false;

	// ...
	if (GetOwner())
	{
		UBoxComponent* boxComp = GetOwner()->FindComponentByClass<UBoxComponent>();
		if (boxComp)
		{
			boxComp->OnComponentBeginOverlap.AddDynamic(this, &ULowLevel_WizardRadius::OnComponentHit);
			boxComp->OnComponentEndOverlap.AddDynamic(this, &ULowLevel_WizardRadius::OnCollisionEnd);
		}
	}
}

void ULowLevel_WizardRadius::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		canMove = true;
		wizard->SetCanMove(canMove);
		wizard->SetPlayer(OtherActor);
	}
}

void ULowLevel_WizardRadius::OnCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		canMove = false;
		wizard->SetCanMove(canMove);
	}
}

// Called every frame
void ULowLevel_WizardRadius::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Set the movement speed and interpolation factor
	
}

void ULowLevel_WizardRadius::SetWiz(ULowLevel_WizardAttack* wiz)
{
	wizard = wiz;
}

ULowLevel_WizardAttack* ULowLevel_WizardRadius::GetWiz()
{
	return wizard;
}
