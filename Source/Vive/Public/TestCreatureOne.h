// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitPawn.h"
#include "TestCreatureOne.generated.h"

/**
 * 
 */
UCLASS()
class VIVE_API ATestCreatureOne : public AUnitPawn
{
	GENERATED_BODY()
	
public:
	ATestCreatureOne();

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleCollision;

	UPR OPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
