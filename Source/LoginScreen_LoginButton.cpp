// Fill out your copyright notice in the Description page of Project Settings.

//Standard widge, header, and game class
#include "LoginScreen_LoginButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"

void ULoginScreen_LoginButton::NativeConstruct()
{
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginScreen_LoginButton::LoginButtonOnClicked);
	}

	if (SignUpButton)
	{
		SignUpButton->OnClicked.AddDynamic(this, &ULoginScreen_LoginButton::SignUpButtonOnClicked);
	}
}

void ULoginScreen_LoginButton::LoginButtonOnClicked()
{
	FString username = UsernameInput->GetText().ToString();
	FString password = PasswordInput->GetText().ToString();
	if (username.IsEmpty() || password.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Username or password is empty"));
	}
	else
	{
		Login(username, password);
	}
}

void ULoginScreen_LoginButton::Login(FString username, FString password)
{
	
}

void ULoginScreen_LoginButton::SignUpButtonOnClicked()
{
	UWorld* world = GetWorld();

	if (world)
	{
		FString signUpLevelName = "SignupScreen";
		UGameplayStatics::OpenLevel(world, FName(*signUpLevelName));
	}
}

void SignUp(FString username, FString password)
{
	// Construct the request URL
	FString Url = "https://portals-of-power-default-rtdb.firebaseio.com/players.json";

	// Create a JSON request payload 
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(username))
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField("Username", username);
	//JsonObject->SetStringField("Password", password);
}