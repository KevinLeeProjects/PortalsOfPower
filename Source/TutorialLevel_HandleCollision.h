// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TutorialLevel_TutorialHUD.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PORTALSOFPOWER_API TutorialLevel_HandleCollision
{
public:
	TutorialLevel_HandleCollision();
	~TutorialLevel_HandleCollision();

	static TutorialLevel_HandleCollision& GetInstance();

	bool tutorialInitMove;
	void collisionResponse(const FString& colliderName);

	void SetTutorialHUD(UTutorialLevel_TutorialHUD* Widget);

private: 
	UTutorialLevel_TutorialHUD* MyUserWidgetReference;
};
