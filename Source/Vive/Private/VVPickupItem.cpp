// Fill out your copyright notice in the Description page of Project Settings.


#include "VVPickupItem.h"
#include "ProtoPlayer.h"
#include "InventoryComponent.h"

// Sets default values
AVVPickupItem::AVVPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemID = FName(TEXT("No ID"));
	InteractText = FText::FromString(TEXT("Press Y to pickup"));

}

// Called when the game starts or when spawned
void AVVPickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVVPickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AVVPickupItem::Interact_Implementation(AActor * OtherActor)
{
	auto OtherInventoryComponent = OtherActor->FindComponentByClass<UInventoryComponent>();

	if (OtherInventoryComponent == nullptr)
		return false;

	AInventoryBag* OtherInventoryBag = OtherInventoryComponent->GetInventoryBag();

	//Add item to inventory and destroy actor
	if (OtherInventoryBag->AddItemToInventoryByID(ItemID))
	{
		Destroy();
		return true;
	}

	return false;
}

FText AVVPickupItem::GetInteractText_Implementation() const
{
	return InteractText;
}

bool AVVPickupItem::UseAction_Implementation(AInventoryBag* OwnerInventory, int32 InventoryIndex)
{
	VVLOG(Warning, TEXT("Default UseAction called... Neeeds implementation"));

	/**
	* Use 해도 인벤토리에서 사리지지 않는 아이템들을 위해
	* 사라지는 아이템만 사라지도록
	* RemoveItemByIndex를 InventoryBag이 아닌 여기서 실행하도록 만들었음
	*/
	AInventoryBag* OwnerInventoryBag = Cast<AInventoryBag>(OwnerInventory);
	if (OwnerInventoryBag == nullptr)
	{
		VVLOG(Warning, TEXT("OwnerInventroy invalid"));
		Destroy();
		return false;
	}

	OwnerInventoryBag->RemoveItemByIndex(InventoryIndex);
	Destroy();
	return true;
}

bool AVVPickupItem::DropAction_Implementation(AInventoryBag* OwnerInventory, int32 InventoryIndex)
{

	/**
	* Drop 해도 인벤토리에서 사리지지 않는 아이템들을 위해
	* 사라지는 아이템만 사라지도록
	* RemoveItemByIndex를 InventoryBag이 아닌 여기서 실행하도록 만들었음
	*/
	AInventoryBag* OwnerInventoryBag = Cast<AInventoryBag>(OwnerInventory);
	if (OwnerInventoryBag == nullptr)
	{
		VVLOG(Warning, TEXT("OwnerInventroy invalid"));
		return false;
	}

	OwnerInventoryBag->RemoveItemByIndex(InventoryIndex);

	AActor* ItemUser = Cast<AActor>(OwnerInventory->GetOwner());
	if (ItemUser == nullptr)
	{
		VVLOG(Warning, TEXT("ItemUser invalid"));
		return false;
	}

	// Set PickupItem's location to the item user's location
	FVector ItemUserLocation = ItemUser->GetActorLocation();
	this->SetActorLocation(ItemUserLocation);
	return true;
}