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

protected: 
	//Part 1

	//Login variables
	FString username;
	FString API;
	FString tutorialComplete;
	

	//Tutorial variables
	bool tutorialInitMove;
	bool canAttack;
	bool checkCanAttack;
	bool weaponExplanation;
	bool macaroniExplanation;
	bool canPickUp;
	bool weaponStarExplanation;
	bool itemExplanation;
	float pace;

	//Part 2
	bool healthExplanation;
	bool abilityIntro;
	bool passiveExplanation;
	bool abilityOneExplanation;
	bool abilityOneActive;
	bool canUseAbilityOne;
	float abilityOneCooldown;
	bool ultExplanationIntro;
	bool ultActive;
	bool ultWizardTrain;
	bool canUseUlt;

public:
	
	GlobalVariables();
	~GlobalVariables();

	//Part 1

	//Login functions
	static GlobalVariables& GetInstance();

	void SetAPI(FString& api);
	FString GetAPI();

	void SetUsername(FString& name);
	FString GetUsername();

	void SetTutorialComplete(FString& tComplete);
	FString GetTutorialComplete();

	FString GetDBURL();

	//Tutorial functions
	void SetTutorialInitMove(bool& move);
	bool GetTutorialInitMove();

	void SetPace(float speed);
	float GetPace();

	void SetCanAttack(bool& attack);
	bool GetCanAttack();

	void SetCheckCanAttack(bool& check);
	bool GetCheckCanAttack();

	void SetWeaponExplanation(bool& explain);
	bool GetWeaponExplanation();

	void SetMacaroniExplanation(bool& macEx);
	bool GetMacaroniExplanation();

	void SetCanPickUp(bool& pickup);
	bool GetCanPickUp();

	void SetWeaponStarExplanation(bool& explain);
	bool GetWeaponStarExplanation();

	void SetItemExplanation(bool& explain);
	bool GetItemExplanation();


	//Part 2

	void SetHealthExplanation(bool& explain);
	bool GetHealthExplanation();

	void SetAbilityIntro(bool& explain);
	bool GetAbilityIntro();

	void SetPassiveExplanation(bool& explain);
	bool GetPassiveExplanation();

	void SetAbilityOneExplanation(bool& explain);
	bool GetAbilityOneExplanation();

	void SetAbilityOneActive(bool& activate);
	bool GetAbilityOneActive();

	void SetCanUseAbilityOne(bool& cast);
	bool GetCanUseAbilityOne();

	float GetAbilityOneCooldown();

	void SetUltExplanationIntro(bool& explain);
	bool GetUltExplanationIntro();

	void SetUltActive(bool& active);
	bool GetUltActive();

	void SetUltWizardTrain(bool& train);
	bool GetUltWizardTrain();

	void SetCanUseUlt(bool& cast);
	bool GetCanUseUlt();
};
