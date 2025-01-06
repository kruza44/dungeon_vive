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
		/** PerceptionSphere 관련 블랙보드 세팅 */
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

			/** EPerceptionState가 바뀔때마다 SetPerceptionState() 실행 */
			PerceptionSphereComp->OnPerceptionChanged.AddUObject(this, &AVVAIController::SetPerceptionState);
		}

		/** BehaviorTree 작동 */
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

/** EPerceptionState가 바뀔때마다 SetPerceptionState() 실행 */
void AVVAIController::SetPerceptionState()
{
	// 매번 이렇게 받아오는 것보단 PerceptionComp를 저장해두고 쓰는 것이 낫지 않을까..?
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

		// Found 상태일때 TargetUnit에 타겟을 저장, 아니면 비움
		switch (CurrPerceptionState)
		{
		case EPerceptionState::Peace:
		case EPerceptionState::Search:
			Blackboard->SetValueAsObject(TargetUnitKey, nullptr);
			break;
		case EPerceptionState::Found:
			// 임시로 처음 보이는 유닛만 타겟으로 지정하게 만듬... 보완 필요
			AActor* VisibleActorOne = PerceptionSphereComp->VisibleActors[0];
			Blackboard->SetValueAsObject(TargetUnitKey, VisibleActorOne);
			break;
		}
	}
}
