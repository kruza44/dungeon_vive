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
	// 블루프린트로 override 하지 않으면 기본 Implementation 버젼이 실행
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	bool Interact(AActor* OtherActor);


	// Blueprint implementable interfaces에서는 단독 BlueprintCallable 함수가 불가능함
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CanInteract")
	FText GetInteractText() const;


	// Press Y to interact 등 자식 BP에서 블루프린트로 구현함
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool ShowInteractText();


	// Press Y to interact 등 자식 BP에서 블루프린트로 구현함
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanInteract")
	bool HideInteractText();
};
