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
	Interact_Implementation: ��ȣ�ۿ�� �������� �κ��丮�� �߰��ǰ� �Ⱦ� ���͸� �ı���
	Interact: �������Ʈ���� ��� ������. ��ȣ�ۿ�� �߰�����
	ȿ���� �ʿ��� Ư���� ��� �ش� ������ BP���� ����ؼ� �����ϸ� ��.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	bool Interact(AActor* OtherActor);
	virtual bool Interact_Implementation(AActor* OtherActor) override;


	/**
	* �⺻ "Press Y to pickup"�� �ƴ� �ٸ� �ؽ�Ʈ�� �ʿ��ϴٸ�
	* �ش� ������ BP���� InteractText�� �����ϸ� ��
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	FText GetInteractText() const;
	virtual FText GetInteractText_Implementation() const override;


	/**
	* VVPickupItem_BP���� ����ؼ� �����Ǿ� ����.
	* ������ ���� �� InteractText�� ������.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool ShowInteractText();


	/**
	* VVPickupItem_BP���� ����ؼ� �����Ǿ� ����.
	* �ָ� �������� �� InteractText�� ����.
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool HideInteractText();


	/**
	* ������ ����� �ش� ������ BP���� UseAction ��� �� ����
	* ������ ��� �� �κ��丮���� ���ŵǴ� ���
	* Super()�� ����Ƽ�� Implementation ȣ�� �Ŀ� �����ϸ� ��
	* InventroyBag Ŭ�������� ȣ����
	*
	* OwnerInventoryBag->RemoveItemByIndex(InventoryIndex)�� Destroy() �����ؾ���
	* ���ڴ� ���������� ���ڴ� �ʼ���
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool UseAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);
	virtual bool UseAction_Implementation(AInventoryBag* OwnerInventory, int32 InventoryIndex) override;


	/**
	* ����� �������� ��� ����Ƽ�� Implementation �״�� ���ֵ� ��.
	* Ư���� ��쿡�� �ش� ������ BP���� DropAction ��� �� ����
	* InventroyBag Ŭ�������� ȣ����
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanBeInsideInventory")
	bool DropAction(AInventoryBag* OwnerInventory, int32 InventoryIndex);
	virtual bool DropAction_Implementation(AInventoryBag* OwnerInventory, int32 InventoryIndex) override;
};
