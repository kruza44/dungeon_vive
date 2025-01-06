// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "GameFramework/Pawn.h"
#include "UnitPawn.generated.h"

UCLASS()
class VIVE_API AUnitPawn : public APawn
{
	GENERATED_BODY()

public:
	AUnitPawn();

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UUnitStat* UnitStatComponent;

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


public:	
	virtual void Tick(float DeltaTime) override;

	// ���߿� UDamageTypeClass �߰�???
	// PushDirection �������� �а�, HitFromDirection�� �ٶ󺸰� �Ѵ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UnitPawn")
	void CauseDamage(float BaseDamage, float PoiseDamage, float PushPower, FVector PushDirection, FVector HitFromDirection, AActor* DamageCauser, AController* DamageInstigator);
	virtual void CauseDamage_Implementation(float BaseDamage, float PoiseDamage, float PushPower, FVector PushDirection, FVector HitFromDirection, AActor* DamageCauser, AController* DamageInstigator);


	//float GetFinalDamage
	//float GetFinalAttackRange

};
