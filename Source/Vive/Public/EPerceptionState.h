// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EPerceptionState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPerceptionState : uint8
{
	Peace UMETA(DisplayName = "Peace"),
	Search UMETA(DisplayName = "Search"),
	Found UMETA(DisplayName = "Found")
};