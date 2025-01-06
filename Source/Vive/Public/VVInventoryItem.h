// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PaperSprite.h"
#include "VVInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct FVVInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	FVVInventoryItem()
	{
		ItemID = FName(TEXT("NoID"));
		ItemActor = nullptr;
		Name = FText::FromString(TEXT("NoName"));
		Weight = 0;
		Thumbnail = nullptr;
		Description = FText::FromString(TEXT("No Description"));
		ActionText = FText::FromString(TEXT("No Action"));
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ActionText;

	bool operator==(const FVVInventoryItem& OtherItem) const
	{
		if (ItemID == OtherItem.ItemID)
			return true;
		return false;
	}
};