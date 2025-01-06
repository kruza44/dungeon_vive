// Fill out your copyright notice in the Description page of Project Settings.

#include "VVAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PerceptionSphere.h"

const FName AVVAIController::PerceptionCompKey(TEXT("PerceptionComp"));
const FName AVVAIController::PerceptionStateKey(TEXT("PerceptionState"));
const FName AVVAIController::TargetUnitKey(TEXT("TargetUnit"));

AVVAIController::AVVAIController()
{

}

void AVVAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

#pragma region Run and set Blackboard and BT

	if (UseBlackboard(BBAsset, Blackboard))
	{
		/** PerceptionSphere ���� ������ ���� */
		auto OwnerPerceptionComp = GetPawn()->FindComponentByClass<UPerceptionSphere>();
		if (nullptr == OwnerPerceptionComp)
		{
			VVLOG(Error, TEXT("Couldn't Get Owner's PerceptionSphereComponent..."))
		}
		else
		{
			UPerceptionSphere* PerceptionSphereComp = Cast<UPerceptionSphere>(OwnerPerceptionComp);
			Blackboard->SetValueAsObject(PerceptionCompKey, PerceptionSphereComp);
			Blackboard->SetValueAsEnum(PerceptionStateKey, (uint8)PerceptionSphereComp->GetPerceptionState());

			/** EPerceptionState�� �ٲ𶧸��� SetPerceptionState() ���� */
			PerceptionSphereComp->OnPerceptionChanged.AddUObject(this, &AVVAIController::SetPerceptionState);
		}

		/** BehaviorTree �۵� */
		if (!RunBehaviorTree(BTAsset))
		{
			VVLOG(Error, TEXT("Couldn't run behavior tree..."));
		}
	}

#pragma endregion

}

void AVVAIController::OnUnPossess()
{
}

/** EPerceptionState�� �ٲ𶧸��� SetPerceptionState() ���� */
void AVVAIController::SetPerceptionState()
{
	// �Ź� �̷��� �޾ƿ��� �ͺ��� PerceptionComp�� �����صΰ� ���� ���� ���� ������..?
	auto OwnerPerceptionComp = GetPawn()->FindComponentByClass<UPerceptionSphere>();
	if (nullptr == OwnerPerceptionComp)
	{
		VVLOG(Error, TEXT("Couldn't Get Owner's PerceptionSphereComponent..."))
	}
	else
	{
		UPerceptionSphere* PerceptionSphereComp = Cast<UPerceptionSphere>(OwnerPerceptionComp);
		EPerceptionState CurrPerceptionState = PerceptionSphereComp->GetPerceptionState();
		Blackboard->SetValueAsEnum(PerceptionStateKey, (uint8)CurrPerceptionState);

		// Found �����϶� TargetUnit�� Ÿ���� ����, �ƴϸ� ���
		switch (CurrPerceptionState)
		{
		case EPerceptionState::Peace:
		case EPerceptionState::Search:
			Blackboard->SetValueAsObject(TargetUnitKey, nullptr);
			break;
		case EPerceptionState::Found:
			// �ӽ÷� ó�� ���̴� ���ָ� Ÿ������ �����ϰ� ����... ���� �ʿ�
			AActor* VisibleActorOne = PerceptionSphereComp->VisibleActors[0];
			Blackboard->SetValueAsObject(TargetUnitKey, VisibleActorOne);
			break;
		}
	}
}
