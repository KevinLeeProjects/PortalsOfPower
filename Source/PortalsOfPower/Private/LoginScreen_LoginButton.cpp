// Fill out your copyright notice in the Description page of Project Settings.

//Standard widget, header, and game class
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
#include "Logging/LogMacros.h"

//C++
#include<iostream>
#include<algorithm>

//ServerGlobalVariable
#include "../Server/Server_GlobalVariables.h"

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

	//URL for Database
	FString databaseTutorialURL = TEXT("https://portals-of-power-default-rtdb.firebaseio.com/players/" + LOGIN_USERNAME.ToLower() + "/TutorialComplete.json");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(databaseTutorialURL);

	// Set the response callback
	HttpRequest->OnProcessRequestComplete().BindLambda([world, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
		{
			FString toTutorial = Response->GetContentAsString();
			if (world)
			{
				if (toTutorial == "\"true\"")
				{
				//	test();
					FString LevelName = "127.0.0.1.";
					GlobalVariables().GetInstance().SetServerIP(LevelName);
					FString port = "54698";
					GlobalVariables().GetInstance().SetServerPort(port);
					UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
					FString setTutorialComplete = "true";
					GlobalVariables().GetInstance().SetTutorialComplete(setTutorialComplete);
				//FString gameClient = "ServerGameClient";
					//UGameplayStatics::OpenLevel(world, FName(*gameClient));
				}
				else
				{
					FString tutorialLevel = "TutorialLevel";
					UGameplayStatics::OpenLevel(world, FName(*tutorialLevel));
				}
			}
		});


	// Send the HTTP request
	HttpRequest->ProcessRequest();

	
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

void ULoginScreen_LoginButton::test()
{
	Http = &FHttpModule::Get();
	//In the aws_backend.py script, upload api gateway endpoint to firebase database, then do a http request to get it here. Everytime the server updates, it should automatically be checked here.
	ApiGatewayEndpoint = FString::Printf(TEXT("https://1nmou2y4te.execute-api.us-west-1.amazonaws.com/testfleet-api-test-stage"));
	LoginURI = FString::Printf(TEXT("/login"));
	StartSessionURI = FString::Printf(TEXT("/startsession"));
	LoginRequest();
}

//void ULoginScreen_LoginButton::OnLoginClicked()
//{
//	LoginRequest(user, pass);
//}

void ULoginScreen_LoginButton::LoginRequest()
{
	FString usr = "user0";
	FString pwd = "test12";
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("username"), *FString::Printf(TEXT("%s"), *usr));
	JsonObject->SetStringField(TEXT("password"), *FString::Printf(TEXT("%s"), *pwd));

	UE_LOG(LogTemp, Warning, TEXT("About to make login request to %s with %s/%s"),
		*ApiGatewayEndpoint, *usr, *pwd);

	// stick it into JsonBody
	FString JsonBody;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// make http request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> LoginHttpRequest = Http->CreateRequest();
	LoginHttpRequest->SetVerb("POST");
	LoginHttpRequest->SetURL(ApiGatewayEndpoint + LoginURI);
	LoginHttpRequest->SetHeader("Content-Type", "application/json");
	LoginHttpRequest->SetContentAsString(JsonBody);
	LoginHttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginScreen_LoginButton::OnLoginResponse);
	LoginHttpRequest->ProcessRequest();

}

//
// For details on the types of responses that can be returned - look at the login-function lamba
// 
// The successful response will be 200, status: "success"
// Otherwise it is a failure
//
void ULoginScreen_LoginButton::OnLoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bRequestWasSuccessful)
{
	FString LoginError;
	FString IdToken;

	if (!bRequestWasSuccessful)
	{
		LoginError = TEXT("Got Failed Login - Request could not be made - Check your ApiGatewayEndpoint value");
	}
	else if (!Response.IsValid())
	{
		LoginError = TEXT("Got Failed Login - Response is not valid");
	}
	else
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			LoginError = TEXT("Got Failed Login - Could not deserialize response");
		}
		else if (!JsonObject->HasField("status"))
		{
			LoginError = TEXT("Got Failed Login - No status field");
		}
		else
		{
			FString StatusValue = JsonObject->GetStringField("status");
			if (StatusValue != "success")
			{
				LoginError = TEXT("Got Failed Login - Status is not success");
			}
			else if (!JsonObject->HasField("tokens"))
			{			
				LoginError = TEXT("Got Failed Login - No tokens field");
			}
			else
			{
				IdToken = JsonObject->GetObjectField("tokens")->GetStringField("IdToken");
			}
		}
	}

	if (LoginError.IsEmpty())
	{
		StartSessionRequest(IdToken);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LoginError);
		if (Response.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
		}
	}
}

void ULoginScreen_LoginButton::StartSessionRequest(FString idt)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> StartSessionHttpRequest = Http->CreateRequest();
	StartSessionHttpRequest->SetVerb("GET");
	StartSessionHttpRequest->SetURL(ApiGatewayEndpoint + StartSessionURI);
	StartSessionHttpRequest->SetHeader("Content-Type", "application/json");
	StartSessionHttpRequest->SetHeader("Authorization", idt);
	StartSessionHttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginScreen_LoginButton::OnStartSessionResponse);
	StartSessionHttpRequest->ProcessRequest();

}
void ULoginScreen_LoginButton::OnStartSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString PlayerSessionId = JsonObject->GetObjectField("PlayerSession")->GetStringField("PlayerSessionId");
			FString IpAddress = JsonObject->GetObjectField("PlayerSession")->GetStringField("IpAddress");
			FString Port = JsonObject->GetObjectField("PlayerSession")->GetStringField("Port");

			FString LevelName = IpAddress + ":" + Port;
			GlobalVariables().GetInstance().SetServerIP(IpAddress);
			GlobalVariables().GetInstance().SetServerPort(Port);
			FString Options = "?PlayerSessionId=" + PlayerSessionId;

			UE_LOG(LogTemp, Warning, TEXT("LEVEL: %s"), *LevelName);
			UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), false, Options);
		}
	}
}