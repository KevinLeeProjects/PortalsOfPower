// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TutorialLevel_TutorialHUD.generated.h"


/**
 * 
 */
UCLASS()
class PORTALSOFPOWER_API UTutorialLevel_TutorialHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainText;

	void NativeConstruct() override;
};
