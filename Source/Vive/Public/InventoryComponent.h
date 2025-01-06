// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VVInventoryItem.h"
#include "InventoryBag.h"
#include "InventoryComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIVE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "InventoryComponent")
	AInventoryBag* GetInventoryBag();

	/*
	* InventoryBag 추가할때마다 OwnerUnit 할당해주는 함수 필요할지도
	*/

	// Returns -1 when failed
//	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
//	int32 SearchEmptyInventory();
};