// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PaperFlipbook.h"
#include "Weapon.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EWeaponType
{
	WEAP_Sword	UMETA(DisplayName = "Sword"),
	WEAP_Axe UMETA(DisplayName = "Axe"),
	WEAP_Spear UMETA(DisplayName = "Spear"),
	WEAP_Bow UMETA(DisplayName = "Bow")
};

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TEnumAsByte<EWeaponType> WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackRange = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackWidthRange = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<UPaperFlipbook*> Sprites;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//	UNiagaraSystem* SlashEffect;


//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//	TSubclassOf<class AAttackTrailEffect> TrailEffect;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//	USkeletalMesh* TrailHitBox;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//	TArray<UAnimSequence*> AnimVars;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//	UParticleSystem* TrailParticle;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//	UCurveFloat* CurveVar;

};