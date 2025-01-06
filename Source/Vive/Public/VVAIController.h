// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "AIController.h"
#include "VVAIController.generated.h"

/**
 * 
 */
UCLASS()
class VIVE_API AVVAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AVVAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName PerceptionCompKey;
	static const FName PerceptionStateKey;
	static const FName TargetUnitKey;

protected:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere)
	class UBlackboardData* BBAsset;

private:
	void SetPerceptionState();


};
