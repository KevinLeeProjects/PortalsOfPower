// Fill out your copyright notice in the Description page of Project Settings.


#include "Server_ServerGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Server_GlobalVariables.h"
#include "GlobalVariables.h"

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"
#include "Logging/LogMacros.h"

// Include the necessary headers
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include "Containers/Array.h"
#include "GenericPlatform/GenericPlatformString.h"

AServer_ServerGameMode::AServer_ServerGameMode()
{
	// set default pawn class to our Blueprinted character
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GameClient/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	UE_LOG(LogTemp, Warning, TEXT("NEW PLAYER"));
	/*
	//URL for Database
	FString username = GlobalVariables().GetInstance().GetUsername();
	UE_LOG(LogTemp, Warning, TEXT("USERNMAE: %s"), *username);
	FString getClass = TEXT("https://portals-of-power-default-rtdb.firebaseio.com/" + username + "/Characters/Char1/0/Class.json");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(getClass);

	
	// Set the response callback
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful)
		{
			FString className = Response->GetContentAsString();
			className.ReplaceInline(TEXT("\""), TEXT(""), ESearchCase::CaseSensitive);

			UE_LOG(LogTemp, Warning, TEXT("CLASS: %s"), *className);

			//test();
		});

	
	// Send the HTTP request
	HttpRequest->ProcessRequest();
	*/
}

void AServer_ServerGameMode::test()
{
	
}

// Function to receive and process data on the server
void AServer_ServerGameMode::ReceiveDataOnServer(uint8* ReceivedData, int32 ReceivedBytes)
{
	// Deserialize and process the received data
	FString SerializedMessage(reinterpret_cast<const TCHAR*>(ReceivedData));
	FString DataString;
	int32 Value;
	TArray<FString> SplitValues;
	SerializedMessage.ParseIntoArray(SplitValues, TEXT(","), true);

	if (SplitValues.Num() >= 2)
	{
		DataString = SplitValues[0];
		Value = FCString::Atoi(*SplitValues[1]);
	}

	// Process the received data
	UE_LOG(LogTemp, Warning, TEXT("Received data from client: %s, %d"), *DataString, Value);

	// ... perform any necessary server-side logic or actions ...
}

FString ConvertIPToString(const TArray<uint8>& InAddress)
{
	FString IPAddress;
	IPAddress.AppendInt(InAddress[0]);
	IPAddress.AppendChar('.');
	IPAddress.AppendInt(InAddress[1]);
	IPAddress.AppendChar('.');
	IPAddress.AppendInt(InAddress[2]);
	IPAddress.AppendChar('.');
	IPAddress.AppendInt(InAddress[3]);
	return IPAddress;
}

void AServer_ServerGameMode::GetIPAddressAndPort()
{
	// Get the socket subsystem
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	if (SocketSubsystem)
	{
		// Get the local adapter addresses
		TArray<TSharedPtr<FInternetAddr>> LocalAddresses;
		SocketSubsystem->GetLocalAdapterAddresses(LocalAddresses);

		// Loop through the local addresses
		for (const TSharedPtr<FInternetAddr>& Addr : LocalAddresses)
		{
			FString IPAddress;
			Addr->ToString(false);

			FString Port = FString::FromInt(Addr->GetPort());
			UE_LOG(LogTemp, Display, TEXT("IP Address: %s, Port: %s"), *IPAddress, *Port);
		}
	}
}

// Main server loop
void AServer_ServerGameMode::ServerLoop()
{
	// Create a socket
	FSocket* ListeningSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	// Bind the socket to a port
	FIPv4Endpoint Endpoint(FIPv4Address::Any, 12345);
	ListeningSocket->Bind(*Endpoint.ToInternetAddr());

	// Start listening for connections
	ListeningSocket->Listen(8);

	while (true)
	{
		// Accept a new connection
		FSocket* NewSocket = ListeningSocket->Accept(TEXT("default"));

		// Receive data from the connected client
		TArray<uint8> ReceivedData;
		int32 BytesRead = 0;
		bool bSuccess = NewSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), BytesRead);

		if (bSuccess && BytesRead > 0)
		{
			// Call the function to process the received data
			ReceiveDataOnServer(ReceivedData.GetData(), BytesRead);
		}

		// Clean up the socket
		NewSocket->Close();
		delete NewSocket;
	}

	// Clean up the listening socket
	ListeningSocket->Close();
	delete ListeningSocket;
}