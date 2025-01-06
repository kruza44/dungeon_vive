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
	* VVPickupItem�� Use Action �Լ��� �־
	* VVPickupItem�� ������ �� �װ��� UseAction�� �����Ѵ�.
	* �׷��� �����ϴ� ���� ��������Ʈ�� �ݸ����� �ִ� VVPickupItem�̱� ������
	* ��������Ʈ�� �ݸ����� ��Ȱ��ȭ �� ���¿��� �����ؼ�
	* �����ϰ� �Լ��� �ҷ��� �� �ֵ��� ������ �ʿ��� �� ����
	*/
	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool UseItemByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "InventoryBag")
	bool DropItemByIndex(int32 Index);
};
