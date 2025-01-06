// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBag.h"
#include "CanBeInsideInventory.h"
#include "VVGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AInventoryBag::AInventoryBag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventoryBag::BeginPlay()
{
	Super::BeginPlay();

	ItemSlots.SetNum(AmountOfSlots); //나중에 Resize로 바꿔야?? 근데 KismetArrayLibrary 사용법을 모르겠음
	
}

// Called every frame
void AInventoryBag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInventoryBag::IsSlotEmpty(int32 Index)
{
	//If ItemActor is invalid, the slot is empty
	if (!UKismetSystemLibrary::IsValidClass(ItemSlots[Index].ItemActor))
	{
		return true;
	}

	return false;
}


// If search has failed, returns -1.
int32 AInventoryBag::SearchEmptySlotIndex()
{
	int32 CurrentSlotIndex = 0;
	// Search ItemSlots
	for (CurrentSlotIndex ; CurrentSlotIndex < ItemSlots.Num() ; CurrentSlotIndex++)
	{
		// If Slot's ItemActor is invalid, it is empty
		if (!UKismetSystemLibrary::IsValidClass(ItemSlots[CurrentSlotIndex].ItemActor))
		{
			return CurrentSlotIndex;
		}
	}

	return -1;	// Search failed
}

int32 AInventoryBag::GetInventoryWeight()
{
	int32 Weight = 0;
	int32 CurrentSlotIndex = 0;
	for (CurrentSlotIndex ; CurrentSlotIndex < ItemSlots.Num() ; CurrentSlotIndex++)
	{
		// If the slot is empty, return
		if (!UKismetSystemLibrary::IsValidClass(ItemSlots[CurrentSlotIndex].ItemActor))
		{
			continue;
		}

		Weight += ItemSlots[CurrentSlotIndex].Weight;
	}

	return Weight;
}

bool AInventoryBag::GetItemDataByIndex(int32 Index, FVVInventoryItem& ItemData)
{
	if (IsSlotEmpty(Index))
	{
		return false;
	}

	ItemData = ItemSlots[Index];
	return true;
}

bool AInventoryBag::AddItemToInventoryByID(FName ID)
{
	UVVGameInstance* GameInstance = Cast<UVVGameInstance>(GetWorld()->GetGameInstance());

	//Find item data by datatable row name from GameInstance
	FVVInventoryItem* NewItem = GameInstance->GetVVItemData(ID);

	if (NewItem)
	{
		// 무게 체크
		if ((GetInventoryWeight() + NewItem->Weight) <= InventoryWeightLimit)
		{
			int32 EmptySlotIndex = SearchEmptySlotIndex();
			if (EmptySlotIndex == -1)
			{
				return false;	// Couldn't find empty slot
			}
			ItemSlots[EmptySlotIndex] = *NewItem;
			UpdateInventorySlot(EmptySlotIndex);
			return true;
		}
	}
	return false;	// Add failed
}


bool AInventoryBag::RemoveItemByIndex(int32 Index)
{
	if (!IsSlotEmpty(Index))
	{
		// Empty the slot
		ItemSlots[Index] = FVVInventoryItem();
		UpdateInventorySlot(Index);
		return true;
	}

	return false;	// Remove failed
}


bool AInventoryBag::UseItemByIndex(int32 Index)
{
	if (IsSlotEmpty(Index))
	{
		return false;
	}

	/*
	* PickupItem에 UseAction 함수가 있으므로
	* PickupItem을 스폰한 뒤 그것의 UseAction을 실행한다.
	*/
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ItemSlots[Index].ItemActor, SpawnParams);

	// Check if the item can be used
	ICanBeInsideInventory* UseActionInterface = Cast<ICanBeInsideInventory>(SpawnedActor);
	if (UseActionInterface)
	{
		UseActionInterface->Execute_UseAction(SpawnedActor, this, Index);
		UpdateInventorySlot(Index);
		return true;
	}

	VVLOG(Warning, TEXT("Failed to cast the used item to ICanBeInsideInventory interface"));
	SpawnedActor->Destroy();
	return false;
}

bool AInventoryBag::DropItemByIndex(int32 Index)
{
	if (IsSlotEmpty(Index))
	{
		return false;
	}

	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ItemSlots[Index].ItemActor, SpawnParams);

	// Check if the item can be dropped
	ICanBeInsideInventory* DropActionInterface = Cast<ICanBeInsideInventory>(SpawnedActor);
	if (DropActionInterface)
	{
		DropActionInterface->Execute_DropAction(SpawnedActor, this, Index);
		UpdateInventorySlot(Index);
		return true;
	}

	VVLOG(Warning, TEXT("Failed to cast the dropped item to ICanBeInsideInventory interface"));
	SpawnedActor->Destroy();
	return false;
}
