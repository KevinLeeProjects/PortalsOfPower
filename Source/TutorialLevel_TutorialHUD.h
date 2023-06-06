// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/ProgressBar.h"
#include "TutorialLevel_TutorialHUD.generated.h"


/**
 * 
 */

UCLASS()
class PORTALSOFPOWER_API UTutorialLevel_TutorialHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Part 1 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainText;

	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Inventory;*/

	//Arrows
	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Arrow;*/

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurrentWeaponArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurrentWeaponLevelArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* HealthArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* PassiveArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* AbilityOneArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* AbilityTwoArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UltArrow;

	//Icons

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurrentWeaponIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurrentWeaponLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* Health;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Item;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* NewWeaponLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* PassiveIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* AbilityOneIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* AbilityTwoIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UltIcon;

	TArray<UImage*> iconArray;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HealthText;

	void ShowArrow(int32 num);

	void HideArrow(int32 num);

	void ShowItem();

	void HideItem();

	void SwitchWeapons();

	TArray<UImage*> arrowArray;

	//Cooldown

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AbilityOneCooldown;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* UltCooldown;

	FText abilityOneCooldownText;
	FTimerHandle abilityOneCooldownHandleHUD;
	void AbilityOneCooldownStart();
	float abilityOneCooldown;

	FText ultCooldownText;
	FTimerHandle ultCooldownHandleHUD;
	void UltCooldownStart();
	float ultCooldown;


	//Jurgen Text

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


	//Part 2

	void IntroducePortals();
};
