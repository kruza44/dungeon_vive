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
* ����� ItemID ��� Row �̸����� ã��
* ���߿� ItemID�� ã���� �����ؾ� ��
* �׷��� ItemID�� ã�°� ������ ȿ�������� ���� �𸣰��� 
*/
FVVInventoryItem * UVVGameInstance::GetVVItemData(FName ItemID) const
{
	return VVItemDB->FindRow<FVVInventoryItem>(ItemID, TEXT(""));
}
