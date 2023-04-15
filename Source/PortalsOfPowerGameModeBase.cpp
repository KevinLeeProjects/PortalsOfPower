// Copyright Epic Games, Inc. All Rights Reserved.


#include "PortalsOfPowerGameModeBase.h"
#include "LoginScreen_LoginButton.h"
#include "SignupScreen_SignupButton.h"
#include "Blueprint/UserWidget.h"

void APortalsOfPowerGameModeBase::BeginPlay()
{
	if (IsValid(WidgetClass))
	{
		LoginScreen_LoginButton = Cast<ULoginScreen_LoginButton>(CreateWidget(GetWorld(), WidgetClass));

		if (LoginScreen_LoginButton != nullptr)
		{
			LoginScreen_LoginButton->AddToViewport();
		}
	}
}

