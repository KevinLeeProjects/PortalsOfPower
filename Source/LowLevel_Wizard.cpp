// Fill out your copyright notice in the Description page of Project Settings.

#include "LowLevel_Wizard.h"
#include "LowLevel_WizardHP.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "TutorialLevel_HandleCollision.h"
#include "Components/ActorComponent.h"


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
	/*FString MacaroniBlueprintPath = "/Game/Art/MagicMacaroni/Basic/MagicMacaroni";
	UBlueprint* MacaroniBlueprint = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *MacaroniBlueprintPath));
	if (MacaroniBlueprint)
	{
		macaroniBP = MacaroniBlueprint->GeneratedClass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Blueprint: %s"), *MacaroniBlueprintPath);
	}*/
	TutorialLevel_HandleCollision().GetInstance().SetWizard(this);
	// ...
}


// Called every frame
void ULowLevel_Wizard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FacePlayer();
	// ...
}

void ULowLevel_Wizard::SpawnMacaroni()
{
	UClass* macaroniBP = TutorialLevel_HandleCollision().GetInstance().GetMacaroniBP();
	AActor* Actor2 = GetWorld()->SpawnActor<AActor>(macaroniBP, GetOwner()->GetActorLocation() - FVector(0.0f, 0.0f, 30.0f), GetOwner()->GetActorRotation());
}

void ULowLevel_Wizard::FacePlayer()
{
	//if (TutorialLevel_HandleCollision().GetInstance().GetPlayer())
	//{
	//	// Get the direction from the enemy component to the player
	//	FVector Direction = TutorialLevel_HandleCollision().GetInstance().GetPlayer()->GetActorLocation() - GetOwner()->GetActorLocation();
	//	Direction.Z = 0.0f; // Ensure the enemy only rotates in the XY plane

	//	// Rotate the enemy component to face the player
	//	FRotator TargetRotation = Direction.Rotation() + FRotator(0.0f, -90.0f, 0.0f);
	//	//SetWorldRotation(TargetRotation);
	//	GetOwner()->SetActorRotation(TargetRotation);
	//}
}
