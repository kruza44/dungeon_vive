// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "UnitBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VIVE_API UUnitBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintCallable, Category = "Unit", meta = (DefaultToSelf = "Target"))
		static void WallSlideMove(AActor* Target, FVector MoveDir, float Speed);

	UFUNCTION(BlueprintCallable, Category = "Unit")
		static void SetTargetDir(AActor* Target, UPARAM(ref) FVector& TargetDir, FVector TargetPos);

	/**
	* Speed: PlayMakeró�� OnEnter�� �����Ƿ� tempSpeed�� �����;� �Ѵ�
	* TimerRef: ���������� OnEnter�� ��� ���� ������ ó���� ���� ����
	* SlowTime: �ӵ��� �������� �ֱ�
	* SlowSpeed: �ӵ��� �������� ���� (�������� �и�)
	* StopSpeed: �������� ���߰� �� �ּ� �ӵ�
	* WillStop: StopSpeed�� �ӵ��� �Ǹ� ���� ������ ����
	*/

	// MovementComponent �̻��
	UFUNCTION(BlueprintCallable, Category = "Unit")
		static void SuddenMove(AActor* Target, FVector MoveDirection, UPARAM(ref) float& Speed, UPARAM(ref) float& TimerRef, float SlowTime, float SlowSpeed, float StopSpeed, bool WillStop = false);
	// MovementComponent ���
	UFUNCTION(BlueprintCallable, Category = "Unit")
		static float MovementCompSuddenMove(APawn* Target, FVector MoveDirection, UPARAM(ref) float& Speed, UPARAM(ref) float& TimerRef, float SlowTime, float SlowSpeed, float StopSpeed, bool WillStop = false);

	UFUNCTION(BlueprintCallable, Category = "Unit")
		static int GetAngleNumber(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = "Unit")
		static void SetAngleAnimation(UPaperFlipbookComponent* Target, int AngleNum, UPaperFlipbook* Anim3, UPaperFlipbook* Anim4, UPaperFlipbook* Anim5);
};
