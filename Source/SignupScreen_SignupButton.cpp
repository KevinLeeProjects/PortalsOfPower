// Fill out your copyright notice in the Description page of Project Settings.

//Standard widge, header, and game class
#include "SignupScreen_SignupButton.h"
#include "PortalsOfPowerGameModeBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
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

FString EMAIL;
FString USERNAME;
FString PASSWORD;
FString APIKEY;
FString IDTOKEN;

void USignupScreen_SignupButton::NativeConstruct()
{
	if (SignupButton)
	{
		SignupButton->OnClicked.AddDynamic(this, &USignupScreen_SignupButton::SignupButtonOnClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &USignupScreen_SignupButton::ToLoginScreen);
	}
}

void USignupScreen_SignupButton::SignupButtonOnClicked()
{
	FString username = UsernameInput->GetText().ToString();
	FString email = EmailInput->GetText().ToString();
	FString password = PasswordInput->GetText().ToString();
	FString confirmPassword = ConfirmPasswordInput->GetText().ToString();
	bool state = AgreeBox->IsChecked();

	bool matchingPassword = password == confirmPassword;
	bool noBlankInputs = !(username.IsEmpty() || email.IsEmpty() || password.IsEmpty() || confirmPassword.IsEmpty());

	if (matchingPassword && noBlankInputs && state)
	{
		SignUpUser(email, password, username);
	}
}

void USignupScreen_SignupButton::SignUpUser(FString& Email, FString& Password, FString& Username)
{
	EMAIL = *Email;
	USERNAME = *Username;
	PASSWORD = *Password;

	//URL for Database
	FString databaseAPIURL = TEXT("https://portals-of-power-default-rtdb.firebaseio.com/API.json");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(databaseAPIURL);

	// Set the response callback
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &USignupScreen_SignupButton::CreateAccount);

	// Send the HTTP request
	HttpRequest->ProcessRequest();
}

//Create Firebase user Auth through HTTP request
void USignupScreen_SignupButton::CreateAccount(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
{
	if (Successful && Response.IsValid())
	{
		// Handle the response data here
		FString API = Response->GetContentAsString();
		API.ReplaceInline(TEXT("\""), TEXT(""), ESearchCase::CaseSensitive);
		APIKEY = *API;
		FString authURL = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + API;

		// Create a JSON request payload
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField("email", *EMAIL);
		JsonObject->SetStringField("password", *PASSWORD);
		JsonObject->SetBoolField("returnSecureToken", true);

		// Serialize the JSON payload to a string
		FString JsonString;
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

		// Create an HTTP request
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetVerb("POST");
		HttpRequest->SetURL(authURL);
		HttpRequest->SetHeader("Content-Type", "application/json");
		HttpRequest->SetContentAsString(JsonString);

		HttpRequest->OnProcessRequestComplete().BindUObject(this, &USignupScreen_SignupButton::OnSignInUserResponse);
		
		// Send the HTTP request
		HttpRequest->ProcessRequest();
	}
	else
	{
		// Handle the error
		UE_LOG(LogTemp, Error, TEXT("Failed to retrieve data from Firebase Realtime Database"));
	}
}

void USignupScreen_SignupButton::OnSignInUserResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess && Response->GetResponseCode() == EHttpResponseCodes::Ok)
	{
		// Parse the JSON response
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		// Extract the user token and other information from the JSON response
		FString Token = JsonObject->GetStringField("idToken");
		FString UserId = JsonObject->GetStringField("localId");
		// ... You can extract other relevant data as needed

		IDTOKEN = *Token;

		CreatePlayerDatabase(Request, Response, bSuccess);
	}
	else
	{
		// Handle the error response
		UE_LOG(LogTemp, Error, TEXT("Failed to sign in user: %d %s"), Response->GetResponseCode(), *Response->GetContentAsString());
	}
}

//Create Firebase Realtime Database through HTTP request
void USignupScreen_SignupButton::CreatePlayerDatabase(FHttpRequestPtr databseRequest, FHttpResponsePtr databaseResponse, bool databaseSuccessful)
{
	/*if (databaseSuccessful && databaseResponse->GetResponseCode() == EHttpResponseCodes::Ok)
	{*/
		FString tempUser = *USERNAME;
		FString databaseURL = "https://portals-of-power-default-rtdb.firebaseio.com/players/" + tempUser.ToLower() + ".json";
		// Create a JSON request payload
		TSharedPtr<FJsonObject> databaseJsonObject = MakeShareable(new FJsonObject);
		databaseJsonObject->SetStringField("Email", *EMAIL);
		databaseJsonObject->SetStringField("Username", *USERNAME);
		databaseJsonObject->SetBoolField("TutorialComplete", false);

		// Serialize the JSON payload to a string
		FString databaseJsonString;
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&databaseJsonString);
		FJsonSerializer::Serialize(databaseJsonObject.ToSharedRef(), JsonWriter);

		// Create an HTTP request
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetVerb("PUT");
		HttpRequest->SetURL(databaseURL);
		HttpRequest->SetHeader("Content-Type", "application/json");
		HttpRequest->SetContentAsString(databaseJsonString);

		// Bind a function to handle the HTTP response
		//HttpRequest->OnProcessRequestComplete().BindUObject(this, &USignupScreen_SignupButton::SendEmailVerification);
		
		// Send the HTTP request
		HttpRequest->ProcessRequest();

		FString createCharacterURL = "https://portals-of-power-default-rtdb.firebaseio.com/players/" + tempUser.ToLower() + "/Characters/Char1.json";

		// Create a JSON request payload
		TSharedPtr<FJsonObject> charJsonObject = MakeShareable(new FJsonObject);
		TArray<TSharedPtr<FJsonValue>> charJsonArray;

		// Create a JSON object for the first element
		TSharedPtr<FJsonObject> stats = MakeShareable(new FJsonObject);
		stats->SetNumberField(TEXT("Attack"), 5); 
		stats->SetNumberField(TEXT("Firing Frequency"), 10);
		stats->SetNumberField(TEXT("Pace"), 5);
		stats->SetNumberField(TEXT("Resilience"), 5);
		stats->SetNumberField(TEXT("Health"), 100);
		stats->SetNumberField(TEXT("Health Regeneration Per Second"), 4);
		stats->SetNumberField(TEXT("Luck"), 5);

		TSharedPtr<FJsonObject> charClass = MakeShareable(new FJsonObject);
		charClass->SetStringField(TEXT("Class"), "Chef");

		TSharedPtr<FJsonObject> charLevel = MakeShareable(new FJsonObject);
		charLevel->SetNumberField(TEXT("Exp"), 0);
		charLevel->SetNumberField(TEXT("Level"), 1);

		// Create an FJsonValueObject from the JSON object
		TSharedPtr<FJsonValueObject> JsonValueObject = MakeShareable(new FJsonValueObject(stats));
		TSharedPtr<FJsonValueObject> classJsonValueObject = MakeShareable(new FJsonValueObject(charClass));
		TSharedPtr<FJsonValueObject> levelJsonValueObject = MakeShareable(new FJsonValueObject(charLevel));

		charJsonArray.Add(classJsonValueObject);
		charJsonArray.Add(JsonValueObject);
		charJsonArray.Add(levelJsonValueObject);

		// Set the JSON array as a field in the JSON object
		charJsonObject->SetArrayField(TEXT("CharacterInfo"), charJsonArray);

		// Serialize the JSON payload to a string
		FString charJsonString;
		TSharedRef<TJsonWriter<>> charJsonWriter = TJsonWriterFactory<>::Create(&charJsonString);
		FJsonSerializer::Serialize(charJsonObject.ToSharedRef(), charJsonWriter);

		// Create an HTTP request
		TSharedRef<IHttpRequest> charHttpRequest = FHttpModule::Get().CreateRequest();
		charHttpRequest->SetVerb("PUT");
		charHttpRequest->SetURL(createCharacterURL);
		charHttpRequest->SetHeader("Content-Type", "application/json");
		charHttpRequest->SetContentAsString(charJsonString);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *charJsonString);
		// Bind a function to handle the HTTP response
		charHttpRequest->OnProcessRequestComplete().BindUObject(this, &USignupScreen_SignupButton::SendEmailVerification);

		// Send the HTTP request
		charHttpRequest->ProcessRequest();
	//}
	//else
	//{
	//	// Handle the error
	//	UE_LOG(LogTemp, Error, TEXT("Failed to retrieve data from Firebase Realtime Database"));
	//}
}

void USignupScreen_SignupButton::SendEmailVerification(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess && Response->GetResponseCode() == EHttpResponseCodes::Ok)
	{
		// Create JSON payload for the request
		FString JsonPayload = FString::Printf(TEXT("{\"requestType\":\"VERIFY_EMAIL\",\"idToken\":\"%s\"}"), *IDTOKEN);

		// Set the URL for the Firebase Authentication REST API endpoint
		FString Url = FString::Printf(TEXT("https://identitytoolkit.googleapis.com/v1/accounts:sendOobCode?key=%s"), *APIKEY);

		// Create HTTP request
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetVerb("POST");
		HttpRequest->SetURL(Url);
		HttpRequest->SetHeader("Content-Type", "application/json");
		HttpRequest->SetContentAsString(JsonPayload);

		// Set callback for handling response
		HttpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
			{
				if (bSuccessful && Response.IsValid())
				{
					int32 ResponseCode = Response->GetResponseCode();
					FString ResponseContent = Response->GetContentAsString();

					//if (ResponseCode == 200)
					//{
					//	// Email sent successfully, handle success
					//	UE_LOG(LogTemp, Warning, TEXT("YESSSS"));
					//}
					//else
					//{
					//	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(ResponseCode));
					//}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ERROR"));
				}
			});
		if (FreezeScreen)
		{
			FreezeScreen->SetVisibility(ESlateVisibility::Visible);
			SuccessScreen->SetVisibility(ESlateVisibility::Visible);
			AccountSuccessfullyCreated->SetVisibility(ESlateVisibility::Visible);
			DoneButton->SetVisibility(ESlateVisibility::Visible);
			if (DoneButton)
			{
				DoneButton->OnClicked.AddDynamic(this, &USignupScreen_SignupButton::ToLoginScreen);
			}
		}
		// Send HTTP request
		HttpRequest->ProcessRequest();
	}
	else
	{
		// Handle the error response
		UE_LOG(LogTemp, Error, TEXT("ERROR"));
	}
}

void USignupScreen_SignupButton::ToLoginScreen()
{
	UWorld* world = GetWorld();

	if (world)
	{
		FString loginLevelName = "LoginScreen";
		UGameplayStatics::OpenLevel(world, FName(*loginLevelName));
	}
}
