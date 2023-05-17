// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialHUD.h"
#include "GlobalVariables.h"
#include "TutorialLevel_HandleCollision.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"

void UTutorialLevel_TutorialHUD::NativeConstruct()
{
    DelayBetweenLetters = 0.05f; // The delay between adding each letter (in seconds)
    CurrentLetterIndex = 0; // The index of the current letter being displayed
    //MainText->SetText(FText::FromString(TEXT(": Welcome to Portals of Power!")));
    bool macExplain = false;
    GlobalVariables().GetInstance().SetMacaroniExplanation(macExplain);
    TutorialLevel_HandleCollision().GetInstance().SetTutorialHUD(this);
    FString welcomeMessage = ": Welcome to Portals of Power! Use WASD to move around the room!";
    SetText(welcomeMessage);
}

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

            if (GlobalVariables().GetInstance().GetMacaroniExplanation())
            {
                move = false;
                GlobalVariables().GetInstance().SetTutorialInitMove(move);
                SetText("There will be many monsters in your journey ahead. Every monster has a chance to drop macaroni of varying color depending on rarity.");
                bool macExplain = false;
                GlobalVariables().GetInstance().SetMacaroniExplanation(macExplain);
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