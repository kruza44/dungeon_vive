// Fill out your copyright notice in the Description page of Project Settings.


#include "VVGameInstance.h"
#include "VVInventoryItem.h"

UVVGameInstance::UVVGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ITEMDB(TEXT("DataTable'/Game/Data/Items.Items'"));
	VVCHECK(ITEMDB.Succeeded());
	VVItemDB = ITEMDB.Object;
}

void UVVGameInstance::Init()
{
	Super::Init();
}


/*
* 현재는 ItemID 대신 Row 이름으로 찾음
* 나중에 ItemID로 찾도록 수정해야 함
* 그런데 ItemID로 찾는게 실제로 효율적인지 아직 모르겠음 
*/
FVVInventoryItem * UVVGameInstance::GetVVItemData(FName ItemID) const
{
	return VVItemDB->FindRow<FVVInventoryItem>(ItemID, TEXT(""));
}
