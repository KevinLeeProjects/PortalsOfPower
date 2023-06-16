// Fill out your copyright notice in the Description page of Project Settings.


#include "Server_GlobalVariables.h"

Server_GlobalVariables::Server_GlobalVariables()
{
	currentClass = "";
}

Server_GlobalVariables::~Server_GlobalVariables()
{
}

void Server_GlobalVariables::SetCurrentClass(FString current_class)
{
	currentClass = current_class;
}

FString Server_GlobalVariables::GetCurrentClass()
{
	return currentClass;
}


