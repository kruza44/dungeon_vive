// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "Engine/DataTable.h"
#include "GameplayTags.h"
#include "Engine/GameInstance.h"
#include "VVGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FVVUnitData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


public:
	FVVUnitData() : HP(50.0f), MP(10.0f), SP(30.0f), Strength(5.0f), MagicAbility(5.0f), Perception(5.0f), Defense(3.0f), Speed(5.0f), Poise(5.0f) {}

	//근본 스탯

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MagicAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Perception;

	//부차 스탯

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Poise;


	//Unit의 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FGameplayTag UnitTypeTag;


	/*
	* HitListElse True: HitList 제외 전부 공격
	* HitListElse False: HitList만 공격
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bHitListElse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FGameplayTagContainer HitListTag;

};


/**
 * 
 */
UCLASS()
class VIVE_API UVVGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UVVGameInstance();

	virtual void Init() override;

//	FVVUnitData* GetVVUnitData(FName RowName);

	struct FVVInventoryItem* GetVVItemData(FName ItemID) const;

private:
//	class UDataTable* VVUnitDB
	class UDataTable* VVItemDB;
};
