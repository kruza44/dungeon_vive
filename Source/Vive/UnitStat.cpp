// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitStat.h"
#include "VVGameInstance.h"

// Sets default values for this component's properties
UUnitStat::UUnitStat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUnitStat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UUnitStat::SetBaseAndCurrentStat(FVVUnitData * StatData)
{
	VVCHECK(nullptr != StatData);
	BaseStat = StatData;
	CurrentHP = BaseStat->HP;
	CurrentMP = BaseStat->MP;
	CurrentSP = BaseStat->SP;
	CurrentStr = BaseStat->Strength;
	CurrentMag = BaseStat->MagicAbility;
	CurrentPerception = BaseStat->Perception;
	CurrentDef = BaseStat->Defense;
	CurrentSpeed = BaseStat->Speed;
	CurrentPoise = BaseStat->Poise;
}



void UUnitStat::SetHPDamage(float NewDamage)
{
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, BaseStat->HP);
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UUnitStat::GetAttackDamage()
{
	// 데미지 계산식
	return 0.0f;
}

FGameplayTag UUnitStat::GetUnitType()
{
	return BaseStat->UnitTypeTag;
}

bool UUnitStat::GetbHitListElse()
{
	return BaseStat->bHitListElse;
}

FGameplayTagContainer UUnitStat::GetHitList()
{
	return BaseStat->HitListTag;
}

bool UUnitStat::CheckHitList(FGameplayTag UnitTypeTag)
{
	bool bHasAny = UnitTypeTag.MatchesAny(GetHitList());
	return GetbHitListElse() ? !bHasAny : bHasAny;
}

float UUnitStat::GetHPRatio()
{
	VVCHECK(nullptr != BaseStat, 0.0f);

	return (BaseStat->HP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / BaseStat->HP);
}
