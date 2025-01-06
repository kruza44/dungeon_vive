// Fill out your copyright notice in the Description page of Project Settings.


#include "VVUnitWidget.h"
#include "UnitStat.h"
#include "Components/ProgressBar.h"

void UVVUnitWidget::BindUnitStat(UUnitStat* NewUnitStat)
{
	VVCHECK(nullptr != NewUnitStat);

	CurrentUnitStat = NewUnitStat;
	NewUnitStat->OnHPChanged.AddUObject(this, &UVVUnitWidget::UpdateHPWidget);
}

void UVVUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	VVCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UVVUnitWidget::UpdateHPWidget()
{
	if (nullptr != CurrentUnitStat)
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentUnitStat->GetHPRatio());
		}
	}
}
