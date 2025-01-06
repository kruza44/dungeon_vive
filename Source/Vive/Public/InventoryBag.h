// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VVInventoryItem.h"
#include "InventoryBag.generated.h"

UCLASS(Blueprintable)
class VIVE_API AInventoryBag : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventoryBag();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVVInventoryItem> ItemSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 AmountOfSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 SlotsPerRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 InventoryWeightLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	AActor* OwnerUnit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "InventoryBag")
	void UpdateInventorySlot(int32 EmptySlotIndex);

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool IsSlotEmpty(int32 Index);

	// If search has failed, returns -1
	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	int32 SearchEmptySlotIndex();

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	int32 GetInventoryWeight();

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool GetItemDataByIndex(int32 Index, FVVInventoryItem& ItemData);

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool AddItemToInventoryByID(FName ID);

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool RemoveItemByIndex(int32 Index);

	/*
	* VVPickupItem에 Use Action 함수가 있어서
	* VVPickupItem을 스폰한 뒤 그것의 UseAction을 실행한다.
	* 그런데 스폰하는 것이 스프라이트와 콜리젼이 있는 VVPickupItem이기 때문에
	* 스프라이트랑 콜리젼을 비활성화 한 상태에서 스폰해서
	* 순수하게 함수만 불러올 수 있도록 수정이 필요할 것 같음
	*/
	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool UseItemByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool DropItemByIndex(int32 Index);
};
