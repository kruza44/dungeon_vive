// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "Components/SceneComponent.h"
#include "EPerceptionState.h"
#include "PerceptionSphere.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPerceptionChanged);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIVE_API UPerceptionSphere : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPerceptionSphere();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	EPerceptionState PerceptionState;	//시야 상태 ENUM

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	FString TestHUDString;	//시야 수치 확인용 텍스트

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	TArray<AActor*> VisibleActors;	//보이는 액터들 저장 배열

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float SearchSightRadius;	//SearchSight 반지름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float FoundSightRadius;		//FoundSight 반지름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float SearchSightAngle;		//SearchSight 시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float FoundSightAngle;		//FoundSight 시야각


	// 시야에 감지될 Collision 타입들
	// PerceptionSphere Component를 가진 액터에서 직접 할당함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectTypes;


	UFUNCTION()
	void FindVisibleTargets();
	UFUNCTION()
	EPerceptionState GetPerceptionState();

//	UFUNCTION(BlueprintImplementableEvent, Category = "PerceptionSphere")
//	void PerceptionStateChanged();

	FOnPerceptionChanged OnPerceptionChanged;
		
private:
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
	FTimerHandle PerceptionTimerHandle;

	UPROPERTY()
	int SearchValue;	//Search 상태 수치
	UPROPERTY()
	int FoundValue;		//Found 상태 수치

	void TargetNotInSight();
	void SearchSightState();
	void FoundSightState();

	void PerceptionStateChanged();

};
