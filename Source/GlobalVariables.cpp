// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalVariables.h"
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


FString APIKey;

GlobalVariables::GlobalVariables()
{
}

GlobalVariables::~GlobalVariables()
{
}

GlobalVariables& GlobalVariables::GetInstance()
{
	// Static local variable to ensure only one instance is created
	static GlobalVariables instance;
	return instance;
}

void GlobalVariables::SetAPI(FString& api)
{
	API = *api;
}

FString GlobalVariables::GetAPI()
{
	return API;
}

void GlobalVariables::SetUsername(FString& name)
{
	username = *name;
}

FString GlobalVariables::GetUsername()
{
	return username;
}

FString GlobalVariables::GetDBURL()
{
	return "https://portals-of-power-default-rtdb.firebaseio.com/";
}
