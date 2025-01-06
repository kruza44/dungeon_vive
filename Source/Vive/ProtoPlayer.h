// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "GameFramework/Pawn.h"
#include "UnitPawn.h"
#include "ProtoPlayer.generated.h"

UCLASS()
class VIVE_API AProtoPlayer : public AUnitPawn
{
	GENERATED_BODY()

public:
	AProtoPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	// Perspective, Orthographic 카메라 비교, 테스트용
	enum class ECameraMode
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	void SetCameraMode(ECameraMode NewCameraMode);
	void CameraSwitch();
	ECameraMode CurrentCameraMode = ECameraMode::PERSPECTIVE;

private:
	struct FDataTableRowHandle* StatDataInDataTable;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
