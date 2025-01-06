// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVive, Log, All);
#define VVLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define VVLOG_S(Verbosity) UE_LOG(LogVive, Verbosity, TEXT("%s"), *VVLOG_CALLINFO)
#define VVLOG(Verbosity, Format, ...) UE_LOG(LogVive, Verbosity, TEXT("%s %s"), *VVLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define VVCHECK(Expr, ...) { if(!(Expr)) { VVLOG(Error, TEXT("ASSETION: %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }