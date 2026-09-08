// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/DSPlayerController.h"
#include "DSPlayerController.h"

void ADSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
