// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitBlueprintLibrary.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

void UUnitBlueprintLibrary::WallSlideMove(AActor* Target, FVector MoveDir, float Speed)
{
	float DeltaTime = Target->GetWorld()->GetDeltaSeconds();
	FVector tempDir = MoveDir * Speed * DeltaTime;
	FHitResult Hit;
	Target->AddActorWorldOffset(tempDir, true, &Hit);

	//If blocked, slide along the wall
	if (Hit.IsValidBlockingHit())
	{
//		tempDir = tempDir - UKismetMathLibrary::ProjectVectorOnToVector(tempDir, Hit.Normal);
		tempDir = FVector::VectorPlaneProject(tempDir, Hit.Normal);
		Target->AddActorWorldOffset(tempDir, true);
	}
}

void UUnitBlueprintLibrary::SetTargetDir(AActor* Target, FVector& TargetDir, FVector TargetPos)
{
	//���� ����
	FVector temp = TargetPos - Target->GetActorLocation();

	//������ ����
//	temp *= FVector(1, 1, 0);
	TargetDir.X = temp.X;
	TargetDir.Y = temp.Y;
	TargetDir.Normalize();

//	temp.Normalize();
//	TargetDir = temp;
}

void UUnitBlueprintLibrary::SuddenMove(AActor* Target, FVector MoveDirection, float& Speed, float& TimerRef, float SlowTime, float SlowSpeed, float StopSpeed, bool WillStop)
{
	if (WillStop)
	{
		if (Speed <= StopSpeed)
		{
			return;
		}
	}

	//Move
	WallSlideMove(Target, MoveDirection, Speed);

	//Add Timer
	TimerRef += Target->GetWorld()->GetDeltaSeconds();

//	UE_LOG(LogClass, Log, TEXT("%f"), TimerRef);

	if (TimerRef >= SlowTime)
	{
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("BOBOBOBO"), TimerRef));
		//Reset Timer
		TimerRef = 0;

		Speed /= SlowSpeed;
	}
}

/**
	TODO::
	SlowTime, SlowSpeed �� �̷� ������
	���߿� �� ���ְ� ó�� �ӵ��� �ָ� ���� ������ �� �Լ� ������ ó���ǵ��� 
	��ĥ ��
*/
float UUnitBlueprintLibrary::MovementCompSuddenMove(APawn * Target, FVector MoveDirection, UPARAM(ref) float & Speed, UPARAM(ref) float & TimerRef, float SlowTime, float SlowSpeed, float StopSpeed, bool WillStop)
{
	if (WillStop)
	{
		if (Speed <= StopSpeed)
		{
			return Speed;
		}
	}

	if (Speed <= 4.0f)	// �� �� �̲������� ������ �ְ� ������ ���� �ָ���
	{
		return Speed;
	}

	//Move
	Target->AddMovementInput(MoveDirection, 1.0f, false);

	TimerRef += Target->GetWorld()->GetDeltaSeconds();

	if (TimerRef >= SlowTime)
	{
		TimerRef = 0;
		if (Speed >= 250.0f)
		{
			Speed = 125.0f; // ���� ū �ӵ��� �������̸� �ӵ��� �� ���δ�
		}
		Speed /= SlowSpeed;
		return Speed;
	}

	return Speed;
}

int UUnitBlueprintLibrary::GetAngleNumber(FVector Direction)
{
	//���� Degree�� ����
	float AtanDegree;
	AtanDegree = atan2f(Direction.Y, Direction.X);
	AtanDegree = FMath::RadiansToDegrees(AtanDegree);

	int AngleNumber;

	if (-180 <= AtanDegree && AtanDegree < -90) //-180 ~ -90
		AngleNumber = 1;
	else if (-90 <= AtanDegree && AtanDegree < -45) //-90 ~ -45
		AngleNumber = 6;
	else if (-45 <= AtanDegree && AtanDegree < 0) // -45 ~ 0
		AngleNumber = 5;
	else if (0 <= AtanDegree && AtanDegree < 90) // 0 ~ 90
		AngleNumber = 4;
	else if (90 <= AtanDegree && AtanDegree < 135) // 90 ~ 135
		AngleNumber = 3;
	else if (135 <= AtanDegree && AtanDegree <= 180) // 135~ 180
		AngleNumber = 2;

	if (AngleNumber < 1 || AngleNumber > 6) //AngleNumber�� 1~6 �̿��� ���� ���´ٸ�
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Wrong AngleNumber")));

	return AngleNumber;
}

void UUnitBlueprintLibrary::SetAngleAnimation(UPaperFlipbookComponent* Target, int AngleNum, UPaperFlipbook* Anim3, UPaperFlipbook* Anim4, UPaperFlipbook* Anim5)
{
	FVector OwnerScale = Target->GetComponentScale();
	switch (AngleNum)
	{
		case 1:
		Target->SetFlipbook(Anim4);
		if (OwnerScale.X > 0)
			Target->SetWorldScale3D(FVector(-1, 1, 1));
		break;
		case 2:
		Target->SetFlipbook(Anim3);
		if (OwnerScale.X > 0)
			Target->SetWorldScale3D(FVector(-1, 1, 1));
		break;
		case 3:
		Target->SetFlipbook(Anim3);
		if (OwnerScale.X < 0)
			Target->SetWorldScale3D(FVector(1, 1, 1));
		break;
		case 4:
		Target->SetFlipbook(Anim4);
		if (OwnerScale.X < 0)
			Target->SetWorldScale3D(FVector(1, 1, 1));
		break;
		case 5:
		Target->SetFlipbook(Anim5);
		if (OwnerScale.X < 0)
			Target->SetWorldScale3D(FVector(1, 1, 1));
		break;
		case 6:
		Target->SetFlipbook(Anim5);
		if (OwnerScale.X > 0)
			Target->SetWorldScale3D(FVector(-1, 1, 1));
		break;
	}
}