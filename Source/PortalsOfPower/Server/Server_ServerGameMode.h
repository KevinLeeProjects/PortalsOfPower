// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Server_ServerGameMode.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class AServer_ServerGameMode : public AGameModeBase
{
	GENERATED_BODY()

private: 
	void test();
	void ReceiveDataOnServer(uint8* ReceivedData, int32 ReceivedBytes);
	void ServerLoop();

	void GetIPAddressAndPort();
	
public: 
	AServer_ServerGameMode();
};
