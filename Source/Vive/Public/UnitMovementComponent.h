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

	// Movement Component 상속
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

	// 달릴 때 속도에 곱하는 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float SpeedBoostMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float AirControlRatio;

	// 추락중에 서 있는 자세에서 떨어지는 자세로 변하는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Movment Component")
	float FallPostureSwitchDelay;

	// Surface로 지정할 채널
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

	//SetComponeneOwner 함수??

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	virtual bool IsSprinting() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	FVector GetFallingVelocity() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	FVector GetMovementVelocity() const;

	// +면 점프 중, -면 떨어지는 중
	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	float GetCurrentFallingSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	float GetCurrentWalkSpeed() const;

	// 공중에 떠 있는 시간. 바닥에 서 있으면 0으로 초기화 됨
	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	float GetInAirTime() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	bool GetbIsInAir() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	bool GetbIsJumping() const;

	UFUNCTION(BlueprintCallable, Category = "Unit|UnitPawnMovement")
	void SetbIsJumping(bool bJump);

protected:

	// 주인 캡슐 컴포넌트
	UCapsuleComponent* CapsuleComponent;

	// 주인 Unit
	class AUnitPawn* UnitOwner;

private:

	bool bIsInAir;
	bool bIsSprinting;
	bool bIsJumping;

	float TimeInAir;
	float LastWalkSpeed;

};
