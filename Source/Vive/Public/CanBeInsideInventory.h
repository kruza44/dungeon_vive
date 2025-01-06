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
	// 아이템 사용 효과 구현용. 블루프린트로 override 하지 않으면 기본 Implementation 버젼이 실행
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool UseAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);


	// 아이템 드랍 효과 구현용. 블루프린트로 override 하지 않으면 기본 Implementation 버젼이 실행
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool DropAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);


	/**
	* 이거 삭제해도 되는 함수인가?
	* VVPickupItem에도 구현되어 있지 않은 것 같고 (왜 컴파일 오류가 안뜨는지 모르겠음)
	* 무기나 방어구 같은 장비 때문에 부적합한 함수명 같기도 함
	* 아무튼 나중에 다시 확인 후 수정 필요
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool IsConsumingItem();
};
