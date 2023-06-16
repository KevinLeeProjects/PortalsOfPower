// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginScreen_LoginButton.generated.h"
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PORTALSOFPOWER_API ULoginScreen_LoginButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* UsernameInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* PasswordInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* LoginButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* UsernameText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PasswordText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DontHaveAnAccountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SignUpButton;

	virtual void NativeConstruct() override;

	virtual void SearchUsername(const FString& username, const FString& password);

	void GetAPI(FString& username, FString& password);

	void GetEmailFromUsername(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);

	void SignInUser();

	void OnSignInUserResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);

	void OpenGameClient();


	UFUNCTION()
	void LoginButtonOnClicked();

	UFUNCTION()
	void SignUpButtonOnClicked();

private: 
	FHttpModule* Http;
	void test();
	void LoginRequest();
	void OnLoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void StartSessionRequest(FString idt);
	void OnStartSessionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(EditAnywhere)
		FString ApiGatewayEndpoint;

	UPROPERTY(EditAnywhere)
		FString LoginURI;

	UPROPERTY(EditAnywhere)
		FString StartSessionURI;
};