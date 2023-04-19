// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialHUD.h"
#include "GlobalVariables.h"
#include "Components/TextBlock.h"

void UTutorialLevel_TutorialHUD::NativeConstruct()
{
	MainText->SetText(FText::FromString(TEXT("Welcome to Portals of Power!")));
}