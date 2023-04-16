// Fill out your copyright notice in the Description page of Project Settings.

//Standard widge, header, and game class
#include "LoginScreen_LoginButton.h"
#include "GlobalVariables.h"
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

//C++
#include<iostream>
#include<algorithm>

FString LOGIN_EMAIL;
FString LOGIN_USERNAME;
FString LOGIN_PASSWORD;
FString API_KEY;
//FString IDTOKEN;
FString UNIQUE_KEY;

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
		GetAPI(username, password);
	}
}

void ULoginScreen_LoginButton::GetAPI(FString& username, FString& password)
{
	//URL for Database
	FString databaseAPIURL = TEXT("https://portals-of-power-default-rtdb.firebaseio.com/API.json");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(databaseAPIURL);

	// Set the response callback
	HttpRequest->OnProcessRequestComplete().BindLambda([this, username, password](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
		{
			FString API = Response->GetContentAsString();
			API.ReplaceInline(TEXT("\""), TEXT(""), ESearchCase::CaseSensitive);
			API_KEY = *API;
			GlobalVariables().GetInstance().SetAPI(API_KEY);
			SearchUsername(username, password);
		});
	
	
	// Send the HTTP request
	HttpRequest->ProcessRequest();
}

void ULoginScreen_LoginButton::SearchUsername(const FString& username, const FString& password)
{
	LOGIN_USERNAME = *username;
	LOGIN_PASSWORD = *password;
	FString authURL = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + API_KEY;
	// Construct the REST API URL
	FString URL = TEXT("https://portals-of-power-default-rtdb.firebaseio.com/players/" + username.ToLower() + ".json");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(URL);

	//HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginScreen_LoginButton::GetUniqueKey);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginScreen_LoginButton::GetEmailFromUsername);
	// Send the HTTP request
	HttpRequest->ProcessRequest();
}

void ULoginScreen_LoginButton::GetEmailFromUsername(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
{
	if (bSuccessful && Response.IsValid())
	{
		// Handle the response data here
		FString ResponseStr = Response->GetContentAsString();

		// Parse the JSON data into a FJsonDom
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			FString jsonEmail;

			if (JsonObject->TryGetStringField("Email", jsonEmail))
			{
				LOGIN_EMAIL = *jsonEmail;
				SignInUser();
			}
		}
	}
	else
	{
		// Handle the error
		UE_LOG(LogTemp, Error, TEXT("Failed to retrieve data from Firebase Realtime Database"));
	}
}

void ULoginScreen_LoginButton::SignInUser()
{
	// Construct the request URL
	FString Url = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + API_KEY;
	
	// Create a JSON request payload
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("email", LOGIN_EMAIL);
	JsonObject->SetStringField("password", LOGIN_PASSWORD);
	JsonObject->SetBoolField("returnSecureToken", true);

	// Serialize the JSON payload to a string
	FString JsonString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// Create an HTTP request
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetURL(Url);
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetContentAsString(JsonString);

	// Bind a function to handle the HTTP response
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginScreen_LoginButton::OnSignInUserResponse);

	// Send the HTTP request
	HttpRequest->ProcessRequest();
}

void ULoginScreen_LoginButton::OnSignInUserResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
{
	if (bSuccessful && Response->GetResponseCode() == EHttpResponseCodes::Ok)
	{
		// Parse the JSON response
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		// Extract the user token and other information from the JSON response
		FString Token = JsonObject->GetStringField("idToken");
		FString UserId = JsonObject->GetStringField("localId");
		// ... You can extract other relevant data as needed
	
		// Handle the successful response
		GlobalVariables().GetInstance().SetUsername(LOGIN_USERNAME);
		OpenGameClient();
	}
	else
	{
		// Handle the error response
		UE_LOG(LogTemp, Error, TEXT("Failed to sign in user: %d %s"), Response->GetResponseCode(), *Response->GetContentAsString());
	}
}

void ULoginScreen_LoginButton::OpenGameClient()
{
	UWorld* world = GetWorld();

	if (world)
	{
		FString gameClient = "GameClient";
		UGameplayStatics::OpenLevel(world, FName(*gameClient));
	}
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