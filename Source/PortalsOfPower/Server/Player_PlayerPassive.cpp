// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_PlayerPassive.h"

// Sets default values
APlayer_PlayerPassive::APlayer_PlayerPassive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayer_PlayerPassive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_PlayerPassive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

