// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UnitMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VIVE_API UUnitMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	UUnitMovementComponent();


	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Movement Component ���
	virtual bool IsMovingOnGround() const override;
	virtual bool IsFalling() const override;
	virtual void StopMovementImmediately() override;


	//Called when the collision capsule touches another primitive component
	//Handles physics interaction logic
	/**UFUNCTION()
	virtual void CapsuleHited(class UPrimitiveComponent* MyComp,
	class AActor* Other,
	class UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit);
	*/

	virtual void ApplyGravity(const FVector& Force, bool bAllowSubstepping, bool bAccelChange);

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	virtual void DoJump();

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	virtual void DoSprint();

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	virtual void DoStopSprint();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float GravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float GravityPower = 980.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	bool bCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float JumpHeight = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float GroundHitToleranceDistance;

	// �޸� �� �ӵ��� ���ϴ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float SpeedBoostMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float AirControlRatio;

	// �߶��߿� �� �ִ� �ڼ����� �������� �ڼ��� ���ϴ� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float FallPostureSwitchDelay;

	// Surface�� ������ ä��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	bool bDebugEnable;
	
	//TraceShapeScale
	//bEnablePhysicsInteraction
	//float HitForceFactor = 0.25f
	//bool bHitForceScaledToMass

	FHitResult CurrentStandingSurface;
	//FHitResult CurrentTracedSurface;
	//FHitResult CapsuleHitResult;

	//SetComponeneOwner �Լ�??

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	virtual bool IsSprinting() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	FVector GetFallingVelocity() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	FVector GetMovementVelocity() const;

	// +�� ���� ��, -�� �������� ��
	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	float GetCurrentFallingSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	float GetCurrentWalkSpeed() const;

	// ���߿� �� �ִ� �ð�. �ٴڿ� �� ������ 0���� �ʱ�ȭ ��
	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	float GetInAirTime() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	bool GetbIsInAir() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	bool GetbIsJumping() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	void SetbIsJumping(bool bJump);

protected:

	// ���� ĸ�� ������Ʈ
	UCapsuleComponent* CapsuleComponent;

	// ���� Unit
	class AUnitPawn* UnitOwner;

private:

	bool bIsInAir;
	bool bIsSprinting;
	bool bIsJumping;

	float TimeInAir;
	float LastWalkSpeed;

};
