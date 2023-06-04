// Fill out your copyright notice in the Description page of Project Settings.


#include "LowLevel_WizardAttack.h"
#include "Components/StaticMeshComponent.h"
#include "TutorialLevel_HandleCollision.h"
//#include "Components/WidgetComponent.h"
//#include "Blueprint/UserWidget.h"
#include "Engine/World.h"

// Sets default values for this component's properties
ULowLevel_WizardAttack::ULowLevel_WizardAttack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULowLevel_WizardAttack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//TArray<UStaticMeshComponent*> StaticMeshComponents;
	//GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	//// Iterate through each static mesh component and process it as per your requirements
	//for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("HIKKK: %s"), *StaticMeshComponent->GetName());
	//	// Do something with the static mesh component
	//}

	
	
	//UE_LOG(LogTemp, Warning, TEXT("HIK: %s"), *WidgetComp->GetName());
}


// Called every frame
void ULowLevel_WizardAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FacePlayer();
	// ...
}

void ULowLevel_WizardAttack::FacePlayer()
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

//void ULowLevel_WizardAttack::TakeDamage(float damage)
//{
//	/*UWidgetComponent* WidgetComp = GetOwner()->FindComponentByClass<UWidgetComponent>();
//	UClass* test = WidgetComp->GetClass()->GetSuperClass();
//	ULowLevel_WizardHP* testOne = Cast<ULowLevel_WizardHP>(test);
//	testOne->TakeDamage(damage);*/
//}