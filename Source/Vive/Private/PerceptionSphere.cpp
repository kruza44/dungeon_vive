// Fill out your copyright notice in the Description page of Project Settings.

#include "PerceptionSphere.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"


/**
* ��ü���� �ν��ϱ� ���� �þ� ���
* �����þ�(SearchSight), �����þ�(FoundSight) �ΰ��� �þ� ����
*
* �����þ�(SearchSight)�� ������ Search ���°� �ǰ� SearchValue�� ��� ����
* SearchValue�� 100 �̻��� �Ǹ� Found ���·� ��ȯ
* SearchValue�� 0���� �������� Peace ���·� ��ȯ
*
* �����þ�(FoundSight)�� ������ Found ���°� �ǰ� FoundValue�� ��� ����
* FoundValue�� 100 ���δ� �� �� ����
* FoundValue�� 0���� �������� Search ���·� ��ȯ
*
* OverlappedActors �迭�� SphereOverlapActors�� ����������
* �þ߸� ���� ��ֹ�, �þ߰�, FoundSight ���� ��� ���� ����
* VisibleActors �迭�� Owner ���Ͱ� ���� ������ ��
* 
* SightState�� �ٲ��ٴ� ���� Owner ���Ϳ� �˸������� OnPerceptionChanged.Broadcast ���
* Owner ���Ͱ� �������Ʈ �̺�Ʈ �׷������� �̺�Ʈ�� ����
*/


/**
* TODO
*
* 1. HitList �� ��ȣ���迡 ���� �ൿ�̳� �ν��� �޶�� �Ѵ�
*
*/


// ������
UPerceptionSphere::UPerceptionSphere()
{
	PrimaryComponentTick.bCanEverTick = true;

	PerceptionState = EPerceptionState::Peace;	//Peace ���·� �ʱ�ȭ
	SearchValue = 0;	//Search ��ġ �ʱ�ȭ
	FoundValue = 0;		//Found ��ġ �ʱ�ȭ

	ActorsToIgnore.Emplace(GetOwner());		//Owner ����
}


void UPerceptionSphere::BeginPlay()
{
	Super::BeginPlay();


	// 0.3�� ������ �� 0.2�ʸ��� FindVisibleTargets ���� Ÿ�̸� 
	GetOwner()->GetWorldTimerManager().SetTimer(PerceptionTimerHandle, this, &UPerceptionSphere::FindVisibleTargets, 0.2F, true, 0.3F);
}


void UPerceptionSphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//�þ� �����
	DrawDebugCone(GetWorld(), GetComponentLocation(), GetForwardVector(), SearchSightRadius, FMath::DegreesToRadians(SearchSightAngle), 0, 12, FColor::Green, false, -1.0F, 0, 1.0F);
	DrawDebugCone(GetWorld(), GetComponentLocation(), GetForwardVector(), FoundSightRadius, FMath::DegreesToRadians(FoundSightAngle), 0, 12, FColor::Orange, false, -1.0F, 0, 1.0F);

	//�þ� ��ġ ������ ����ġ
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
		TestHUDString.Append(FString::FromInt(SearchValue)); //? ���� �þ� ��ġ �߰�
		break;
	case EPerceptionState::Found :
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("wo")));
		TestHUDString.Empty();
		TestHUDString = FString(TEXT("!"));
		TestHUDString.Append(FString::FromInt(FoundValue)); //! ���� �þ� ��ġ �߰�
		break;
	}	//������� �þ� ��ġ ������
}



/**
* 1. 0.2�ʸ��� VisibleActors �ʱ�ȭ, �þ� ��ġ ����
* 2. SearchSight ������ ũ���� SphereOverlapActors ����, OverlappedActors �迭�� ����
* 3. SearchSightAngle �˻� -> ��ֹ� �˻� -> FoundSightAngle �˻� -> FoundSight ������ �˻�
* 4. ���� ���: FoundSightState() �Լ� ����
* 5. SearchSightAngle �˻�, ��ֹ� �˻� ���: SearchSightState() �Լ� ����
* 6. ���� �����: TargetNotInSight() �Լ� ����
*/
void UPerceptionSphere::FindVisibleTargets()
{
	//���̴� ���͵� �ʱ�ȭ
	VisibleActors.Empty();

	TArray<AActor*> OverlappedActors;

	//�þ��� ��ġ ����
	FVector SightLocation = GetComponentLocation();

	// Overlap�� ���͵��� OverlappedActors �迭�� ����
	UKismetSystemLibrary::SphereOverlapActors(this, SightLocation, SearchSightRadius, TargetObjectTypes, nullptr, ActorsToIgnore, OverlappedActors);


	// �ϳ��� ������ ���Ͱ� �ִٸ�
	if (OverlappedActors.IsValidIndex(0))
	{
		for (int32 i = 0; i < OverlappedActors.Num(); i++)
		{
			//Ÿ���� ��ġ
			FVector VisibleActorLocation = OverlappedActors[i]->GetActorLocation();

			// ������ ����, Normalize�ؼ� Ÿ���� ���� ����
			FVector DirToTarget = VisibleActorLocation - SightLocation; 
			DirToTarget.Z = 0;
			DirToTarget.Normalize();


			//���� �þ߰�
			float SightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(GetForwardVector(), DirToTarget)));
			if (SearchSightAngle >= SightAngle)
			{
				//��ֹ� �˻�
				FHitResult OutHit;
				if (!GetWorld()->LineTraceSingleByChannel(OutHit, SightLocation, VisibleActorLocation, ECC_Visibility))
				{
					//���� �þ߰�
					if (FoundSightAngle >= SightAngle)
					{
						//���� �þ� �Ÿ�
						float DistFromTarget = ((VisibleActorLocation - SightLocation) * FVector(1, 1, 0)).Size();
						if (FoundSightRadius >= DistFromTarget)
						{
							//FoundSightState �Լ� ����
							DrawDebugLine(GetWorld(), SightLocation, VisibleActorLocation, FColor::Cyan, false, 0.2F, 0.0F, 2.0F);
							VisibleActors.Emplace(OverlappedActors[i]);
							FoundSightState();

							return;
						}
					}



					//SearchSightState �Լ� ����
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
* Peace ����: 
* Search ����:
*		SearchValue 2�� ����
*		SearchValue�� 0 ���Ϸ� �������� Peace ���·� ��ȯ, Broadcast
* Found ����:
*		FoundValue 2�� ����
*		FoundValue�� 0 ���Ϸ� �������� Search ���·� ��ȯ, Broadcast
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
* Peace ����:
*		Search ���·� ��ȯ, Broadcast
* Search ����:
*		SearchValue�� 50 ���ϸ� 50���� ����
*		50 �̻��̸� 1�� ����
*		100 �̻��� �Ǹ� FoundValue 50���� �ʱ�ȭ, Found ���·� ��ȯ, Broadcast
* Found ����:
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
* Peace ����:
*		Found ���·� ��ȯ, Broadcast
* Search ����:
*		Found ���·� ��ȯ, Broadcast
* Found ����:
*		FoundValue�� 50 ���ϸ� 50���� ����
*		50 �̻��̸� 2�� ����
*		100 �̻��̸� 100���� ����
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
	//�Լ��� �ƴ϶� Delegate�� �ؾ��� ����
}