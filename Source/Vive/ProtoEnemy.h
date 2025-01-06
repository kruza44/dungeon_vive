// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "GameFramework/Pawn.h"
#include "UnitPawn.h"
#include "ProtoEnemy.generated.h"

/**
 * 
 */
UCLASS()
class VIVE_API AProtoEnemy : public AUnitPawn
{
	GENERATED_BODY()
	
public:
	AProtoEnemy();

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	/*
	UFUNCTION(BlueprintNativeEvent, Category = "AIVariables")
		void GetPerceptionLocRot(FVector &OutLocation, FRotator &OutRotation) const;
		void GetPerceptionLocRot_Implementation(FVector &OutLocation, FRotator &OutRotation) const;
	*/



protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
//	virtual void Tick(float DeltaTime) override;

//	virtual void GetActorEyesViewPoint(FVector &Location, FRotator &Rotataion) const override;
	
};
