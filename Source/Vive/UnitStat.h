// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "UnitStat.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate)
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate)

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIVE_API UUnitStat : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUnitStat();


private:
	struct FVVUnitData* BaseStat = nullptr;

	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentMP;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentSP;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentStr;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentMag;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentPerception;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentDef;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentSpeed;
	UPROPERTY(Transient, VisibleAnywhere, Category = CurrentStat, Meta = (AllowPrivateAccess = true))
	float CurrentPoise;

protected:
	virtual void BeginPlay() override;

public:
	void SetBaseAndCurrentStat(FVVUnitData* StatData);
	void SetHPDamage(float NewDamage);
	float GetAttackDamage();
	float GetHPRatio();
	FGameplayTag GetUnitType();
	bool GetbHitListElse();
	FGameplayTagContainer GetHitList();

	//UFUNCTION
	bool CheckHitList(FGameplayTag UnitTypeTag);

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
};
