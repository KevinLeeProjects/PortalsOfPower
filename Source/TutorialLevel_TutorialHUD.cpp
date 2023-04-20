// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLevel_TutorialHUD.h"
#include "GlobalVariables.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"

void UTutorialLevel_TutorialHUD::NativeConstruct()
{
    DelayBetweenLetters = 0.1f; // The delay between adding each letter (in seconds)
    CurrentLetterIndex = 0; // The index of the current letter being displayed
    //MainText->SetText(FText::FromString(TEXT(": Welcome to Portals of Power!")));
    FString welcomeMessage = ": Welcome to Portals of Power!";
    SetText(welcomeMessage);
}

void UTutorialLevel_TutorialHUD::Dialogue_Welcome()
{
	//MainText->SetText(FText::FromString(TEXT(": Welcome to Portals of Power!")));
    //UpdateText(": Welcome to Portals of Power!");
    //UE_LOG(LogTemp, Warning, TEXT("Welcome"));
}

void UTutorialLevel_TutorialHUD::SetText(FString& text)
{
    mainText = *text;
    UpdateText();
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
    }
}

// Call this method to start the text animation
void UTutorialLevel_TutorialHUD::StartTextAnimation()
{
    MainText->SetText(FText::FromString(TEXT(""))); // Clear the text of the UText object
    CurrentLetterIndex = 0; // Reset the index of the current letter
    GetWorld()->GetTimerManager().SetTimer(TextTimerHandle, this, &UTutorialLevel_TutorialHUD::UpdateText, DelayBetweenLetters, false); // Start the timer to update the text
}