// Fill out your copyright notice in the Description page of Project Settings.


#include "VVPlayerController.h"

void AVVPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}