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

	virtual void SearchUsername(FString& username, FString& password);

	void GetAPI(FString& username, FString& password);

	void GetEmailFromUsername(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);

	void GetUniqueKey(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);

	void SignInUser();

	void OnSignInUserResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessful);

	void OpenGameClient();

	UFUNCTION()
	void LoginButtonOnClicked();

	UFUNCTION()
	void SignUpButtonOnClicked();
};


/*
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyDs_iehl0C6EAofubuo_JGfsFZHvgXiew4",
  authDomain: "portals-of-power.firebaseapp.com",
  projectId: "portals-of-power",
  storageBucket: "portals-of-power.appspot.com",
  messagingSenderId: "344750660393",
  appId: "1:344750660393:web:55dfaec64586b9b3167538",
  measurementId: "G-7V00CTXHXP"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
*/