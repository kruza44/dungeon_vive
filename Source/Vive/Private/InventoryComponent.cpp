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
여기서 아이템 추가하도록 고쳐야함... 귀찮으니 나중에
이렇게 하면 두번 비어있는 slot을 찾게 되기 때문.....
일단 지금은 인벤토리를 하나만 사용할 예정이기 때문에
인벤토리 여러개 넣는 기능을 구현할때 고쳐야함

int32 UInventoryComponent::SearchEmptyInventory()
{
	int32 CurrentInventoryIndex = 0;
	for (auto& Inventory : Inventories)	//포인터는 다르게 해야하나? 수정필요?
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
