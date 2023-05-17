// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalVariables.h"
#include "Kismet/GameplayStatics.h"
#include "TutorialLevel_TutorialHUD.h"

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
	tutorialInitMove = false;
	canAttack = false;
	checkCanAttack = false;
	macaroniExplanation = false;
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

//Login
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

void GlobalVariables::SetTutorialComplete(FString& tComplete)
{
	tutorialComplete = *tComplete;
}

FString GlobalVariables::GetTutorialComplete()
{
	return tutorialComplete;
}

FString GlobalVariables::GetDBURL()
{
	return "https://portals-of-power-default-rtdb.firebaseio.com/";
}




//Tutorial
void GlobalVariables::SetTutorialInitMove(bool& move)
{
	tutorialInitMove = move;
}

bool GlobalVariables::GetTutorialInitMove()
{
	return tutorialInitMove;
}

void GlobalVariables::SetCanAttack(bool& attack)
{
	canAttack = attack;
}

bool GlobalVariables::GetCanAttack()
{
	return canAttack;
}

void GlobalVariables::SetCheckCanAttack(bool& check)
{
	checkCanAttack = check;
}

bool GlobalVariables::GetCheckCanAttack()
{
	return checkCanAttack;
}

void GlobalVariables::SetMacaroniExplanation(bool& macEx)
{
	macaroniExplanation = macEx;
}

bool GlobalVariables::GetMacaroniExplanation()
{
	return macaroniExplanation;
}