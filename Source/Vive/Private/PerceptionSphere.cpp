// Fill out your copyright notice in the Description page of Project Settings.

#include "PerceptionSphere.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"


/**
* 개체끼리 인식하기 위한 시야 기능
* 간접시야(SearchSight), 직접시야(FoundSight) 두가지 시야 존재
*
* 간접시야(SearchSight)에 닿으면 Search 상태가 되고 SearchValue가 계속 오름
* SearchValue가 100 이상이 되면 Found 상태로 전환
* SearchValue가 0으로 떨어지면 Peace 상태로 전환
*
* 직접시야(FoundSight)에 닿으면 Found 상태가 되고 FoundValue가 계속 오름
* FoundValue는 100 위로는 더 안 오름
* FoundValue가 0으로 떨어지면 Search 상태로 전환
*
* OverlappedActors 배열은 SphereOverlapActors에 감지됐지만
* 시야를 막는 장애물, 시야각, FoundSight 등은 고려 안한 상태
* VisibleActors 배열은 Owner 액터가 직접 가져다 씀
* 
* SightState가 바꼈다는 것을 Owner 액터에 알리기위해 OnPerceptionChanged.Broadcast 사용
* Owner 액터가 블루프린트 이벤트 그래프에서 이벤트를 받음
*/


/**
* TODO
*
* 1. HitList 등 우호관계에 따라 행동이나 인식이 달라야 한다
*
*/


// 생성자
UPerceptionSphere::UPerceptionSphere()
{
	PrimaryComponentTick.bCanEverTick = true;

	PerceptionState = EPerceptionState::Peace;	//Peace 상태로 초기화
	SearchValue = 0;	//Search 수치 초기화
	FoundValue = 0;		//Found 수치 초기화

	ActorsToIgnore.Emplace(GetOwner());		//Owner 무시
}


void UPerceptionSphere::BeginPlay()
{
	Super::BeginPlay();


	// 0.3초 딜레이 후 0.2초마다 FindVisibleTargets 실행 타이머 
	GetOwner()->GetWorldTimerManager().SetTimer(PerceptionTimerHandle, this, &UPerceptionSphere::FindVisibleTargets, 0.2F, true, 0.3F);
}


void UPerceptionSphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//시야 디버그
	DrawDebugCone(GetWorld(), GetComponentLocation(), GetForwardVector(), SearchSightRadius, FMath::DegreesToRadians(SearchSightAngle), 0, 12, FColor::Green, false, -1.0F, 0, 1.0F);
	DrawDebugCone(GetWorld(), GetComponentLocation(), GetForwardVector(), FoundSightRadius, FMath::DegreesToRadians(FoundSightAngle), 0, 12, FColor::Orange, false, -1.0F, 0, 1.0F);

	//시야 수치 디버깅용 스위치
	switch (PerceptionState)
	{
	case EPerceptionState::Peace :
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("we")));
		TestHUDString.Empty();
		TestHUDString = FString(TEXT("0"));
		break;
	case EPerceptionState::Search :
		TestHUDString.Empty();
		TestHUDString = FString(TEXT("?"));
		TestHUDString.Append(FString::FromInt(SearchValue)); //? 옆에 시야 수치 추가
		break;
	case EPerceptionState::Found :
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("wo")));
		TestHUDString.Empty();
		TestHUDString = FString(TEXT("!"));
		TestHUDString.Append(FString::FromInt(FoundValue)); //! 옆에 시야 수치 추가
		break;
	}	//여기까지 시야 수치 디버깅용
}



/**
* 1. 0.2초마다 VisibleActors 초기화, 시야 위치 갱신
* 2. SearchSight 반지름 크기의 SphereOverlapActors 실행, OverlappedActors 배열에 저장
* 3. SearchSightAngle 검사 -> 장애물 검사 -> FoundSightAngle 검사 -> FoundSight 반지름 검사
* 4. 전부 통과: FoundSightState() 함수 실행
* 5. SearchSightAngle 검사, 장애물 검사 통과: SearchSightState() 함수 실행
* 6. 전부 불통과: TargetNotInSight() 함수 실행
*/
void UPerceptionSphere::FindVisibleTargets()
{
	//보이는 액터들 초기화
	VisibleActors.Empty();

	TArray<AActor*> OverlappedActors;

	//시야의 위치 갱신
	FVector SightLocation = GetComponentLocation();

	// Overlap된 액터들은 OverlappedActors 배열에 저장
	UKismetSystemLibrary::SphereOverlapActors(this, SightLocation, SearchSightRadius, TargetObjectTypes, nullptr, ActorsToIgnore, OverlappedActors);


	// 하나라도 감지된 액터가 있다면
	if (OverlappedActors.IsValidIndex(0))
	{
		for (int32 i = 0; i < OverlappedActors.Num(); i++)
		{
			//타겟의 위치
			FVector VisibleActorLocation = OverlappedActors[i]->GetActorLocation();

			// 높이차 제거, Normalize해서 타겟의 방향 구함
			FVector DirToTarget = VisibleActorLocation - SightLocation; 
			DirToTarget.Z = 0;
			DirToTarget.Normalize();


			//간접 시야각
			float SightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(GetForwardVector(), DirToTarget)));
			if (SearchSightAngle >= SightAngle)
			{
				//장애물 검사
				FHitResult OutHit;
				if (!GetWorld()->LineTraceSingleByChannel(OutHit, SightLocation, VisibleActorLocation, ECC_Visibility))
				{
					//직접 시야각
					if (FoundSightAngle >= SightAngle)
					{
						//직접 시야 거리
						float DistFromTarget = ((VisibleActorLocation - SightLocation) * FVector(1, 1, 0)).Size();
						if (FoundSightRadius >= DistFromTarget)
						{
							//FoundSightState 함수 실행
							DrawDebugLine(GetWorld(), SightLocation, VisibleActorLocation, FColor::Cyan, false, 0.2F, 0.0F, 2.0F);
							VisibleActors.Emplace(OverlappedActors[i]);
							FoundSightState();

							return;
						}
					}



					//SearchSightState 함수 실행
					DrawDebugLine(GetWorld(), SightLocation, VisibleActorLocation, FColor::Cyan, false, 0.2F, 0.0F, 2.0F);
					VisibleActors.Emplace(OverlappedActors[i]);
					SearchSightState();

					return;
				}
			}
		}
	}

	TargetNotInSight();
}

EPerceptionState UPerceptionSphere::GetPerceptionState()
{
	return PerceptionState;
}


/**
* Peace 상태: 
* Search 상태:
*		SearchValue 2씩 감소
*		SearchValue가 0 이하로 떨어지면 Peace 상태로 전환, Broadcast
* Found 상태:
*		FoundValue 2씩 감소
*		FoundValue가 0 이하로 떨어지면 Search 상태로 전환, Broadcast
*/
void UPerceptionSphere::TargetNotInSight()
{
	switch (PerceptionState)
	{
	case EPerceptionState::Peace :
		break;
	case EPerceptionState::Search :
		SearchValue -= 2;
		if (SearchValue <= 0)
		{
			PerceptionState = EPerceptionState::Peace;
			VVLOG(Warning, TEXT("Peace State"));
			OnPerceptionChanged.Broadcast();
		}
		break;
	case EPerceptionState::Found :
		FoundValue -= 2;
		if (FoundValue <= 0)
		{
			PerceptionState = EPerceptionState::Search;
			VVLOG(Warning, TEXT("Search State"));
			OnPerceptionChanged.Broadcast();
		}
		break;
	}
}


/**
* Peace 상태:
*		Search 상태로 전환, Broadcast
* Search 상태:
*		SearchValue가 50 이하면 50으로 고정
*		50 이상이면 1씩 증가
*		100 이상이 되면 FoundValue 50으로 초기화, Found 상태로 전환, Broadcast
* Found 상태:
*/
void UPerceptionSphere::SearchSightState()
{
	switch(PerceptionState)
	{
	case EPerceptionState::Peace :
		PerceptionState = EPerceptionState::Search;
		VVLOG(Warning, TEXT("Search State"));
		OnPerceptionChanged.Broadcast();
		break;
	case EPerceptionState::Search :
		if (SearchValue < 50)
		{
			SearchValue = 50;
		}
		else
		{
			SearchValue += 1;

			if (SearchValue >= 100)
			{
				FoundValue = 50;
				PerceptionState = EPerceptionState::Found;
				VVLOG(Warning, TEXT("Found State"));
				OnPerceptionChanged.Broadcast();
			}
		}
		break;
	case EPerceptionState::Found :
		break;
	}
}


/**
* Peace 상태:
*		Found 상태로 전환, Broadcast
* Search 상태:
*		Found 상태로 전환, Broadcast
* Found 상태:
*		FoundValue가 50 이하면 50으로 고정
*		50 이상이면 2씩 증가
*		100 이상이면 100으로 고정
*/
void UPerceptionSphere::FoundSightState()
{
	switch (PerceptionState)
	{
	case EPerceptionState::Peace :
	case EPerceptionState::Search :
		FoundValue = 50;
		PerceptionState = EPerceptionState::Found;
		VVLOG(Warning, TEXT("Found State"));
		OnPerceptionChanged.Broadcast();
		break;
	case EPerceptionState::Found :
		if (FoundValue < 50)
		{
			FoundValue = 50;
		}
		else if (FoundValue >= 100)
		{
			FoundValue = 100;
		}
		else
		{
			FoundValue += 2;
		}
		break;
	}
}

void UPerceptionSphere::PerceptionStateChanged()
{
	//함수가 아니라 Delegate로 해야할 것임
}