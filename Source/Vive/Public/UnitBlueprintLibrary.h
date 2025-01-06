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
	* Speed: PlayMaker처럼 OnEnter가 없으므로 tempSpeed를 가져와야 한다
	* TimerRef: 마찬가지로 OnEnter가 없어서 지역 변수로 처리할 수가 없다
	* SlowTime: 속도가 느려지는 주기
	* SlowSpeed: 속도가 느려지는 정도 (나눗셈의 분모)
	* StopSpeed: 움직임을 멈추게 될 최소 속도
	* WillStop: StopSpeed의 속도가 되면 멈출 것인지 여부
	*/

	// MovementComponent 미사용
	UFUNCTION(BlueprintCallable, Category = "Unit")
		static void SuddenMove(AActor* Target, FVector MoveDirection, UPARAM(ref) float& Speed, UPARAM(ref) float& TimerRef, float SlowTime, float SlowSpeed, float StopSpeed, bool WillStop = false);
	// MovementComponent 사용
	UFUNCTION(BlueprintCallable, Category = "Unit")
		static float MovementCompSuddenMove(APawn* Target, FVector MoveDirection, UPARAM(ref) float& Speed, UPARAM(ref) float& TimerRef, float SlowTime, float SlowSpeed, float StopSpeed, bool WillStop = false);

	UFUNCTION(BlueprintCallable, Category = "Unit")
		static int GetAngleNumber(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = "Unit")
		static void SetAngleAnimation(UPaperFlipbookComponent* Target, int AngleNum, UPaperFlipbook* Anim3, UPaperFlipbook* Anim4, UPaperFlipbook* Anim5);
};
