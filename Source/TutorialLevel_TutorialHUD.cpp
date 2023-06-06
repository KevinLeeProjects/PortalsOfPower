// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialHUD.h"
#include "GlobalVariables.h"
#include "TutorialLevel_HandleCollision.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

//UE5 Text and float conversion
#include "Internationalization/Text.h"
#include "GenericPlatform/GenericPlatformMath.h"

#include "Engine/Texture2D.h"  // Include the Texture2D header if working with textures
#include "Materials/MaterialInstanceDynamic.h"  // Include the MaterialInstanceDynamic header if working with materials

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"

void UTutorialLevel_TutorialHUD::NativeConstruct()
{
    abilityOneCooldownText = FText::FromString(TEXT(""));
    abilityOneCooldown = 3.0f;

    ultCooldownText = FText::FromString(TEXT(""));
    ultCooldown = 8.0f;

    AbilityOneCooldown->SetText(abilityOneCooldownText);
    UltCooldown->SetText(ultCooldownText);

    arrowArray.Add(CurrentWeaponArrow);
    arrowArray.Add(CurrentWeaponLevelArrow);
    arrowArray.Add(ItemArrow);
    arrowArray.Add(PassiveArrow);
    arrowArray.Add(AbilityOneArrow);
    arrowArray.Add(AbilityTwoArrow);
    arrowArray.Add(UltArrow);
    arrowArray.Add(HealthArrow);

    iconArray.Add(CurrentWeaponIcon);
    iconArray.Add(CurrentWeaponLevel);
    iconArray.Add(Item);
    iconArray.Add(NewWeaponLevel);
    iconArray.Add(PassiveIcon);
    iconArray.Add(AbilityOneIcon);
    iconArray.Add(AbilityTwoIcon);
    iconArray.Add(UltIcon);

    Item->SetVisibility(ESlateVisibility::Hidden);
    ItemLabel->SetVisibility(ESlateVisibility::Hidden);
    NewWeaponLevel->SetVisibility(ESlateVisibility::Hidden);
    //Arrow->SetVisibility(ESlateVisibility::Hidden);

    for (int i = 0; i < arrowArray.Num(); i++)
    {
        arrowArray[i]->SetVisibility(ESlateVisibility::Hidden);
    }

    DelayBetweenLetters = 0.05f; // The delay between adding each letter (in seconds)
    CurrentLetterIndex = 0; // The index of the current letter being displayed
    //MainText->SetText(FText::FromString(TEXT(": Welcome to Portals of Power!")));
    bool macExplain = false;
    GlobalVariables().GetInstance().SetMacaroniExplanation(macExplain);
    TutorialLevel_HandleCollision().GetInstance().SetTutorialHUD(this);
    FString welcomeMessage = "Welcome to Portals of Power! Use WASD to move around the room!";
    SetText(welcomeMessage);
}

//Part 1

void UTutorialLevel_TutorialHUD::Dialogue_Welcome()
{
	//MainText->SetText(FText::FromString(TEXT(": Welcome to Portals of Power!")));
    //UpdateText(": Welcome to Portals of Power!");
    //UE_LOG(LogTemp, Warning, TEXT("Welcome"));
}

void UTutorialLevel_TutorialHUD::SetText(const FString& text)
{
    mainText = *text;
    StartTextAnimation();
}

FString UTutorialLevel_TutorialHUD::GetText()
{
    return mainText;
}

void UTutorialLevel_TutorialHUD::UpdateText()
{
    FString CurrentText = mainText.Left(CurrentLetterIndex + 1); // Get the current text to display
    MainText->SetText(FText::FromString(CurrentText)); // Set the text of the UText object to the current text
    CurrentLetterIndex++; // Increment the index of the current letter

    if (CurrentLetterIndex < mainText.Len()) // If there are more letters to display
    {
        GetWorld()->GetTimerManager().SetTimer(TextTimerHandle, this, &UTutorialLevel_TutorialHUD::UpdateText, DelayBetweenLetters, false); // Start the timer to update the text again
        bool move = false;
        GlobalVariables().GetInstance().SetTutorialInitMove(move);
    }
    else
    {
            bool move = true;
            GlobalVariables().GetInstance().SetTutorialInitMove(move);

            if (GlobalVariables().GetInstance().GetCheckCanAttack())
            {
                bool canAttack = true;
                GlobalVariables().GetInstance().SetCanAttack(canAttack);
            }

            //if (GlobalVariables().GetInstance().GetMacaroniExplanation())
            //{
            //    move = false;
            //    GlobalVariables().GetInstance().SetTutorialInitMove(move);
            //   // SetText("I will explain everything soon");
            //    bool macExplain = false;
            //    GlobalVariables().GetInstance().SetMacaroniExplanation(macExplain);
            //    UE_LOG(LogTemp, Warning, TEXT("HERE"));
            //}

            if (GlobalVariables().GetInstance().GetWeaponStarExplanation())
            {
                HideArrow(0);
                move = false;
                GlobalVariables().GetInstance().SetTutorialInitMove(move);
                //SetText("You may have noticed this box appear. This is the loot inside of the macaroni! ");
                ShowArrow(1);
                //ShowItem();
                SetText("These stars represent the level of your weapon.                                           ");
                bool macexplain = false;
                GlobalVariables().GetInstance().SetWeaponStarExplanation(macexplain);

                bool itemExplain = true;
                GlobalVariables().GetInstance().SetItemExplanation(itemExplain);
            }
            else if (GlobalVariables().GetInstance().GetItemExplanation())
            {
                HideArrow(1);
           
                move = false;
                GlobalVariables().GetInstance().SetTutorialInitMove(move);

                ShowItem();

                bool itemExplain = false;
                GlobalVariables().GetInstance().SetItemExplanation(itemExplain);

                ShowArrow(2);
                SetText("This is the weapon inside of the macaroni! Press F to pick it up.                                           ");

                bool canPickUp = true;
                GlobalVariables().GetInstance().SetCanPickUp(canPickUp);
            }
            else if (GlobalVariables().GetInstance().GetHealthExplanation())
            {
                bool healthExplain = false;
                GlobalVariables().GetInstance().SetHealthExplanation(healthExplain);

                HideArrow(2);
                ShowArrow(7);
                SetText("This is your health bar. When it reaches 0, you die and you lose your current weapon. So make sure to avoid enemy attacks!                   ");

                bool abilityIntroExplain = true;
                GlobalVariables().GetInstance().SetAbilityIntro(abilityIntroExplain);
            }
            else if (GlobalVariables().GetInstance().GetAbilityIntro())
            {
                HideArrow(7);
                bool abilityIntroExplain = false;
                GlobalVariables().GetInstance().SetAbilityIntro(abilityIntroExplain);

                SetText("Now I'll be explaining your abilities. You are currently the chef class, whose role is to be a support character. To explain your first ability, you'll have to take a little damage.                    ");

                TutorialLevel_HandleCollision().GetInstance().PlayerTakeDamage(50);

                bool passiveExplain = true;
                GlobalVariables().GetInstance().SetPassiveExplanation(passiveExplain);
            }
            else if (GlobalVariables().GetInstance().GetPassiveExplanation())
            {
                ShowArrow(3);

                bool passiveExplain = false;
                GlobalVariables().GetInstance().SetPassiveExplanation(passiveExplain);

                SetText("This is your passive ability. This specific ability lets you regenerate health for you and nearby allies. And the best part is, you don't have to click any buttons! It automatically casts!                    ");

                TutorialLevel_HandleCollision().GetInstance().SetPassiveRingVisibility(true);

                bool abilityOneExplain = true;
                GlobalVariables().GetInstance().SetAbilityOneExplanation(abilityOneExplain);
            }
            else if (GlobalVariables().GetInstance().GetAbilityOneExplanation())
            {
                HideArrow(3);

                ShowArrow(4);
                bool abilityOneExplain = false;
                GlobalVariables().GetInstance().SetAbilityOneExplanation(abilityOneExplain);

                SetText("This is your main ability. This specific ability gives you and allies a temporary speed boost! You can use the ability by pressing Q and once you do, you can't use it for another 3 seconds. Try zooming to the portal on the other side of this room!                   ");

                bool abiltyOneActivate = true;
                GlobalVariables().GetInstance().SetAbilityOneActive(abiltyOneActivate);

                bool canUseAbilityOne = true;
                GlobalVariables().GetInstance().SetCanUseAbilityOne(canUseAbilityOne);
            }
            else if (GlobalVariables().GetInstance().GetUltExplanationIntro())
            {
                ShowArrow(6);
                SetText("By pressing spacebar, you throw a blob of food waste which damages enemies within the area. Try it out on the wizard ahead of us! But be careful, he will shoot back this time.                   ");

                bool ultExplain = false;
                GlobalVariables().GetInstance().SetUltExplanationIntro(ultExplain);

                bool ultWizardTrain = true;
                GlobalVariables().GetInstance().SetUltWizardTrain(ultWizardTrain);
            }
            else if (GlobalVariables().GetInstance().GetUltWizardTrain())
            {
            
                HideArrow(6);

                bool setUltActive = true;
                GlobalVariables().GetInstance().SetUltActive(setUltActive);

                bool ultActive = true;
                GlobalVariables().GetInstance().SetCanUseUlt(ultActive);

                bool getUltWizardTrain = false;
                GlobalVariables().GetInstance().SetUltWizardTrain(getUltWizardTrain);
            }
            else if (GlobalVariables().GetInstance().GetOutro())
            {

                GetWorld()->GetTimerManager().ClearTimer(ultCooldownHandleHUD);

                GetWorld()->GetTimerManager().ClearTimer(abilityOneCooldownHandleHUD);

                FString username = GlobalVariables().GetInstance().GetUsername();
                FString databaseURL = "https://portals-of-power-default-rtdb.firebaseio.com/players/" + username.ToLower() + ".json";

                FString RequestBody = "{\"TutorialComplete\": \"true\"}"; // JSON payload with the new value

                TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
                HttpRequest->SetVerb("PATCH");
                HttpRequest->SetURL(databaseURL);
                HttpRequest->SetContentAsString(RequestBody);

                UWorld* world = GetWorld();
                HttpRequest->OnProcessRequestComplete().BindLambda([world](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
                    {
                        FString gameClient = "GameClient";
                        UGameplayStatics::OpenLevel(world, FName(*gameClient));
                    });

                // Send the HTTP request
                HttpRequest->ProcessRequest();

            }
    }
}

// Call this method to start the text animation
void UTutorialLevel_TutorialHUD::StartTextAnimation()
{
    MainText->SetText(FText::FromString(TEXT(""))); // Clear the text of the UText object
    CurrentLetterIndex = 0; // Reset the index of the current letter
    GetWorld()->GetTimerManager().SetTimer(TextTimerHandle, this, &UTutorialLevel_TutorialHUD::UpdateText, DelayBetweenLetters, false); // Start the timer to update the text
}

void UTutorialLevel_TutorialHUD::ShowArrow(int32 num)
{
    arrowArray[num]->SetVisibility(ESlateVisibility::Visible);
}

void UTutorialLevel_TutorialHUD::HideArrow(int32 num)
{
    arrowArray[num]->SetVisibility(ESlateVisibility::Hidden);
}

void UTutorialLevel_TutorialHUD::ShowItem()
{
    Item->SetVisibility(ESlateVisibility::Visible);
    NewWeaponLevel->SetVisibility(ESlateVisibility::Visible);
    ItemLabel->SetVisibility(ESlateVisibility::Visible);
    TutorialLevel_HandleCollision().GetInstance().ExplainMacaroni();
}


void UTutorialLevel_TutorialHUD::HideItem()
{
    Item->SetVisibility(ESlateVisibility::Hidden);
    ItemLabel->SetVisibility(ESlateVisibility::Hidden);
    NewWeaponLevel->SetVisibility(ESlateVisibility::Hidden);
    //TutorialLevel_HandleCollision().GetInstance().ExplainMacaroni();
}

void UTutorialLevel_TutorialHUD::SwitchWeapons()
{
    SetText("Look at in front of us! A portal opened up! Let's step inside");

    const FSlateBrush* CurrentWeaponIconBrush = &(CurrentWeaponIcon->Brush);
    const FSlateBrush* ItemBrush = &(Item->Brush);

    CurrentWeaponIcon->SetBrush(*ItemBrush);

    const FSlateBrush* CurrentWeaponLevelBrush = &(CurrentWeaponLevel->Brush);
    const FSlateBrush* NewWeaponLevelBrush = &(NewWeaponLevel->Brush);

    CurrentWeaponLevel->SetBrush(*NewWeaponLevelBrush);

    HideItem();
    HideArrow(2);
    //Item->SetBrush(*Brush1);
}

//Part 2

void UTutorialLevel_TutorialHUD::IntroducePortals()
{
    SetText("We just went through a portal! You're going to see lots of those once you're on your adventure                   ");
    bool healthExplain = true;
    GlobalVariables().GetInstance().SetHealthExplanation(healthExplain);
}

void UTutorialLevel_TutorialHUD::AbilityOneCooldownStart()
{
    AbilityOneCooldown->SetText(FText::AsNumber(abilityOneCooldown));
    GetWorld()->GetTimerManager().SetTimer(abilityOneCooldownHandleHUD, [=]() mutable
        {
            abilityOneCooldown--;
            AbilityOneCooldown->SetText(FText::AsNumber(abilityOneCooldown));
            if (abilityOneCooldown == 0)
            {
                GetWorld()->GetTimerManager().ClearTimer(abilityOneCooldownHandleHUD);
                abilityOneCooldown = 3.0f;
                AbilityOneCooldown->SetText(FText::FromString(TEXT("")));
            }
            else
            {
                AbilityOneCooldownStart();
            }
        }, 1, false);
}

void UTutorialLevel_TutorialHUD::UltCooldownStart()
{
    UltCooldown->SetText(FText::AsNumber(ultCooldown));
    GetWorld()->GetTimerManager().SetTimer(ultCooldownHandleHUD, [=]() mutable
        {
            ultCooldown--;
            UltCooldown->SetText(FText::AsNumber(ultCooldown));
            if (ultCooldown == 0)
            {
                GetWorld()->GetTimerManager().ClearTimer(ultCooldownHandleHUD);
                ultCooldown = 8.0f;
                UltCooldown->SetText(FText::FromString(TEXT("")));
            }
            else
            {
                UltCooldownStart();
            }
        }, 1, false);
}