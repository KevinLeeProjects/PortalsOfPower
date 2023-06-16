// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PORTALSOFPOWER_API Server_GlobalVariables
{
private:
	FString currentClass;

public:
	Server_GlobalVariables();
	~Server_GlobalVariables();

	void SetCurrentClass(FString current_class);
	FString GetCurrentClass();
	
};
