// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "Blueprint/UserWidget.h"
#include "VVUnitWidget.generated.h"

/**
 * 
 */
UCLASS()
class VIVE_API UVVUnitWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindUnitStat(class UUnitStat* NewUnitStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	class UUnitStat* CurrentUnitStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
	
};
