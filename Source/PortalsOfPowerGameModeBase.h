// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortalsOfPowerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTALSOFPOWER_API APortalsOfPowerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void test();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Class Types")
	TSubclassOf<UUserWidget> WidgetClass; //Specifies base class and assigns a specific class inside of blueprint

	/*UPROPERTY(EditAnywhere, Category = "Class Types")
	TSubclassOf<UUserWidget> WidgetClass;*/

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class ULoginScreen_LoginButton* LoginScreen_LoginButton;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class USignupScreen_SignupButton* SignupScreen_SignupButton;

	virtual void BeginPlay() override;
};
