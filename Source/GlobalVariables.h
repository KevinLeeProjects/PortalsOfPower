// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"

//C++
#include<iostream>
#include<algorithm>

/**
 * 
 */
class PORTALSOFPOWER_API GlobalVariables
{
public:

	//variables
	FString username;
	FString API;

	//functions
	GlobalVariables();
	~GlobalVariables();

	static GlobalVariables& GetInstance();

	void SetAPI(FString& api);
	FString GetAPI();

	void SetUsername(FString& name);
	FString GetUsername();

	FString GetDBURL();
};
