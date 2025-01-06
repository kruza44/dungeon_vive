// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "InventoryBag.h"
#include "CanBeInsideInventory.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCanBeInsideInventory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VIVE_API ICanBeInsideInventory
{
	GENERATED_BODY()

public:
	// ������ ��� ȿ�� ������. �������Ʈ�� override ���� ������ �⺻ Implementation ������ ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool UseAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);


	// ������ ��� ȿ�� ������. �������Ʈ�� override ���� ������ �⺻ Implementation ������ ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool DropAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);


	/**
	* �̰� �����ص� �Ǵ� �Լ��ΰ�?
	* VVPickupItem���� �����Ǿ� ���� ���� �� ���� (�� ������ ������ �ȶߴ��� �𸣰���)
	* ���⳪ �� ���� ��� ������ �������� �Լ��� ���⵵ ��
	* �ƹ�ư ���߿� �ٽ� Ȯ�� �� ���� �ʿ�
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool IsConsumingItem();
};
