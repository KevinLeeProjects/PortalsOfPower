// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "TutorialLevel_TutorialHUD.generated.h"


/**
 * 
 */

UCLASS()
class PORTALSOFPOWER_API UTutorialLevel_TutorialHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainText;

	float DelayBetweenLetters;
	int32 CurrentLetterIndex;
	FTimerHandle TextTimerHandle;

	void UpdateText();
	void StartTextAnimation();

	FString mainText;

	void NativeConstruct() override;
	void Dialogue_Welcome();

	void SetText(const FString& text);
	FString GetText();
};
