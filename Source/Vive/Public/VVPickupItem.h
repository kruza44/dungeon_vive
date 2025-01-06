// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CanInteract.h"
#include "CanBeInsideInventory.h"
#include "VVPickupItem.generated.h"

UCLASS()
class VIVE_API AVVPickupItem : public AActor, public ICanInteract, public ICanBeInsideInventory
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVVPickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractText;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	Interact_Implementation: 상호작용시 아이템이 인벤토리에 추가되고 픽업 액터를 파괴함
	Interact: 블루프린트에서 상속 가능함. 상호작용시 추가적인
	효과가 필요한 특별한 경우 해당 아이템 BP에서 상속해서 구현하면 됨.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	bool Interact(AActor* OtherActor);
	virtual bool Interact_Implementation(AActor* OtherActor) override;


	/**
	* 기본 "Press Y to pickup"가 아닌 다른 텍스트가 필요하다면
	* 해당 아이템 BP에서 InteractText를 수정하면 됨
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	FText GetInteractText() const;
	virtual FText GetInteractText_Implementation() const override;


	/**
	* VVPickupItem_BP에서 상속해서 구현되어 있음.
	* 가까이 갔을 때 InteractText를 보여줌.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool ShowInteractText();


	/**
	* VVPickupItem_BP에서 상속해서 구현되어 있음.
	* 멀리 떨어졌을 때 InteractText를 숨김.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool HideInteractText();


	/**
	* 아이템 기능은 해당 아이템 BP에서 UseAction 상속 후 구현
	* 아이템 사용 후 인벤토리에서 제거되는 경우
	* Super()로 네이티브 Implementation 호출 후에 구현하면 됨
	* InventroyBag 클래스에서 호출함
	*
	* OwnerInventoryBag->RemoveItemByIndex(InventoryIndex)와 Destroy() 구분해야함
	* 전자는 선택이지만 후자는 필수임
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool UseAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);
	virtual bool UseAction_Implementation(AInventoryBag* OwnerInventory, int32 InventoryIndex) override;


	/**
	* 평범한 아이템의 경우 네이티브 Implementation 그대로 냅둬도 됨.
	* 특별한 경우에만 해당 아이템 BP에서 DropAction 상속 후 구현
	* InventroyBag 클래스에서 호출함
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool DropAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);
	virtual bool DropAction_Implementation(AInventoryBag* OwnerInventory, int32 InventoryIndex) override;
};
