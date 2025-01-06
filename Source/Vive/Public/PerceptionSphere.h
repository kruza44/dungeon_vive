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
	EPerceptionState PerceptionState;	//�þ� ���� ENUM

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	FString TestHUDString;	//�þ� ��ġ Ȯ�ο� �ؽ�Ʈ

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	TArray<AActor*> VisibleActors;	//���̴� ���͵� ���� �迭

	UPROPERTY(BlueprintReadOnly, Category = "SightSphere")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float SearchSightRadius;	//SearchSight ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float FoundSightRadius;		//FoundSight ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float SearchSightAngle;		//SearchSight �þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SightSphere")
	float FoundSightAngle;		//FoundSight �þ߰�


	// �þ߿� ������ Collision Ÿ�Ե�
	// PerceptionSphere Component�� ���� ���Ϳ��� ���� �Ҵ���
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
	int SearchValue;	//Search ���� ��ġ
	UPROPERTY()
	int FoundValue;		//Found ���� ��ġ

	void TargetNotInSight();
	void SearchSightState();
	void FoundSightState();

	void PerceptionStateChanged();

};
