// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


/**
���⼭ ������ �߰��ϵ��� ���ľ���... �������� ���߿�
�̷��� �ϸ� �ι� ����ִ� slot�� ã�� �Ǳ� ����.....
�ϴ� ������ �κ��丮�� �ϳ��� ����� �����̱� ������
�κ��丮 ������ �ִ� ����� �����Ҷ� ���ľ���

int32 UInventoryComponent::SearchEmptyInventory()
{
	int32 CurrentInventoryIndex = 0;
	for (auto& Inventory : Inventories)	//�����ʹ� �ٸ��� �ؾ��ϳ�? �����ʿ�?
	{
		int32 EmptySlotIndex = Inventory->SearchEmptySlotIndex();

		// If There's an empty slot in currently searching inventory
		if (EmptySlotIndex != -1)
		{
			return CurrentInventoryIndex;
		}
		CurrentInventoryIndex++;
	}
	return -1;	// Couldn't find empty inventory
}
*/
