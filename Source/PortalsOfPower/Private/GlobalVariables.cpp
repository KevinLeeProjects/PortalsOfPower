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

//Part 1
FString APIKey;

GlobalVariables::GlobalVariables()
{
	serverIP = "";
	serverPort = "";
	tutorialInitMove = false;
	canAttack = false;
	checkCanAttack = false;
	macaroniExplanation = false;
	canPickUp = false;
	weaponExplanation = true;
	weaponStarExplanation = false;
	itemExplanation = false;
	abilityIntro = false;
	abilityOneExplanation = false;
	abilityOneActive = false;
	canUseAbilityOne = false;
	abilityOneCooldown = 3.0f;
	ultExplanationIntro = false;
	ultActive = false;
	ultWizardTrain = false;
	canUseUlt = false;
	outro = false;
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

void GlobalVariables::SetServerIP(FString& ip)
{
	serverIP = ip;
}

FString GlobalVariables::GetServerIP()
{
	return serverIP;
}

void GlobalVariables::SetServerPort(FString& port)
{
	serverPort = port;
}

FString GlobalVariables::GetServerPort()
{
	return serverPort;
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

void GlobalVariables::SetPace(float speed)
{
	pace = speed;
}

float GlobalVariables::GetPace()
{
	return pace;
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

void GlobalVariables::SetWeaponExplanation(bool& explain)
{
	weaponExplanation = explain;
}

bool GlobalVariables::GetWeaponExplanation()
{
	return weaponExplanation;
}

void GlobalVariables::SetMacaroniExplanation(bool& macEx)
{
	macaroniExplanation = macEx;
}

bool GlobalVariables::GetMacaroniExplanation()
{
	return macaroniExplanation;
}

void GlobalVariables::SetCanPickUp(bool& pickup)
{
	canPickUp = pickup;
}

bool GlobalVariables::GetCanPickUp()
{
	return canPickUp;
}

void GlobalVariables::SetWeaponStarExplanation(bool& explain)
{
	weaponStarExplanation = explain;
}

bool GlobalVariables::GetWeaponStarExplanation()
{
	return weaponStarExplanation;
}

void GlobalVariables::SetItemExplanation(bool& explain)
{
	itemExplanation = explain;
}

bool GlobalVariables::GetItemExplanation()
{
	return itemExplanation;
}

//Part 2

void GlobalVariables::SetHealthExplanation(bool& explain)
{
	healthExplanation = explain;
}

bool GlobalVariables::GetHealthExplanation()
{
	return healthExplanation;
}

void GlobalVariables::SetAbilityIntro(bool& explain)
{
	abilityIntro = explain;
}

bool GlobalVariables::GetAbilityIntro()
{
	return abilityIntro;
}

void GlobalVariables::SetPassiveExplanation(bool& explain)
{
	passiveExplanation = explain;
}

bool GlobalVariables::GetPassiveExplanation()
{
	return passiveExplanation;
}

void GlobalVariables::SetAbilityOneExplanation(bool& explain)
{
	abilityOneExplanation = explain;
}

bool GlobalVariables::GetAbilityOneExplanation()
{
	return abilityOneExplanation;
}

void GlobalVariables::SetAbilityOneActive(bool& activate)
{
	abilityOneActive = activate;
}

bool GlobalVariables::GetAbilityOneActive()
{
	return abilityOneActive;
}

void GlobalVariables::SetCanUseAbilityOne(bool& cast)
{
	canUseAbilityOne = cast;
}

bool GlobalVariables::GetCanUseAbilityOne()
{
	return canUseAbilityOne;
}

float GlobalVariables::GetAbilityOneCooldown()
{
	return abilityOneCooldown;
}

void GlobalVariables::SetUltExplanationIntro(bool& explain)
{
	ultExplanationIntro = explain;
}

bool GlobalVariables::GetUltExplanationIntro()
{
	return ultExplanationIntro;
}

void GlobalVariables::SetUltActive(bool& active)
{
	ultActive = active;
}

bool GlobalVariables::GetUltActive()
{
	return ultActive;
}

void GlobalVariables::SetUltWizardTrain(bool& train)
{
	ultWizardTrain = train;
}

bool GlobalVariables::GetUltWizardTrain()
{
	return ultWizardTrain;
}

void GlobalVariables::SetCanUseUlt(bool& cast)
{
	canUseUlt = cast;
}

bool GlobalVariables::GetCanUseUlt()
{
	return canUseUlt;
}

void GlobalVariables::SetOutro(bool& out)
{
	outro = out;
}

bool GlobalVariables::GetOutro()
{
	return outro;
}