// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "LowLevel_WizardHP.generated.h"

/**
 * 
 */
UCLASS()
class PORTALSOFPOWER_API ULowLevel_WizardHP : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* healthProgressBar;

	void UpdateHealth(float damage);

	float health;
};
