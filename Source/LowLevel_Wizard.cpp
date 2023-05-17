// Fill out your copyright notice in the Description page of Project Settings.

#include "LowLevel_WizardHP.h"
#include "Engine/World.h"
#include "TutorialLevel_HandleCollision.h"
#include "Components/ActorComponent.h"
#include "LowLevel_Wizard.h"

// Sets default values for this component's properties
ULowLevel_Wizard::ULowLevel_Wizard()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULowLevel_Wizard::BeginPlay()
{
	Super::BeginPlay();
	FString MacaroniBlueprintPath = "/Game/Art/MagicMacaroni/Basic/MagicMacaroni";
	UBlueprint* MacaroniBlueprint = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *MacaroniBlueprintPath));
	if (MacaroniBlueprint)
	{
		macaroniBP = MacaroniBlueprint->GeneratedClass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Blueprint: %s"), *MacaroniBlueprintPath);
	}
	TutorialLevel_HandleCollision().GetInstance().SetWizard(this);
	// ...
}


// Called every frame
void ULowLevel_Wizard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULowLevel_Wizard::SpawnMacaroni()
{
	AActor* Actor2 = GetWorld()->SpawnActor<AActor>(macaroniBP, GetOwner()->GetActorLocation() - FVector(0.0f, 0.0f, 30.0f), GetOwner()->GetActorRotation());
}

