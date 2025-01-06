// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanInteract.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCanInteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VIVE_API ICanInteract
{
	GENERATED_BODY()

public:
	// �������Ʈ�� override ���� ������ �⺻ Implementation ������ ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	bool Interact(AActor* OtherActor);


	// Blueprint implementable interfaces������ �ܵ� BlueprintCallable �Լ��� �Ұ�����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	FText GetInteractText() const;


	// Press Y to interact �� �ڽ� BP���� �������Ʈ�� ������
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool ShowInteractText();


	// Press Y to interact �� �ڽ� BP���� �������Ʈ�� ������
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool HideInteractText();
};
