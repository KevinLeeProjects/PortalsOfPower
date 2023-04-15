// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//HTTP and JSON
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"

#include "SignupScreen_SignupButton.generated.h"



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PORTALSOFPOWER_API USignupScreen_SignupButton : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* UsernameInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* EmailInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* PasswordInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ConfirmPasswordInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SignupButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* AgreeBox;

	virtual void NativeConstruct() override;

	void SignUpUser(FString& email, FString& password, FString& username);

	void CreatePlayerDatabase(FHttpRequestPtr databseRequest, FHttpResponsePtr databaseResponse, bool databaseSuccessful);

	void CreateAccount(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);

	void OnSignInUserResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

	void SendEmailVerification(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

	UFUNCTION()
	void SignupButtonOnClicked();
};
