// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UUnitMovementComponent::UUnitMovementComponent()
{
	GravityScale = 2.0f;
	GravityPower = 980.0f;
	bCanJump = true;
	JumpHeight = 200.0f;
	GroundHitToleranceDistance = 20.0f;
	SpeedBoostMultiplier = 1.5f;
	AirControlRatio = 0.5f;
	FallPostureSwitchDelay = 0.5f;

	DrawDebugType = EDrawDebugTrace::None;

	// Floating Pawn Movement
	MaxSpeed = 300.0f;
	Acceleration = 2048.0f;
	Deceleration = 2048.0f;
}

void UUnitMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	VVCHECK(nullptr != UpdatedComponent);

	CapsuleComponent = Cast<UCapsuleComponent>(UpdatedComponent);

	TimeInAir = 0.0f;
	bIsInAir = true;
	LastWalkSpeed = MaxSpeed;
}

void UUnitMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	VVCHECK(nullptr != CapsuleComponent);

	const ECollisionChannel CollisionChannel = CapsuleComponent->GetCollisionObjectType();
	const FVector TraceStart = CapsuleComponent->GetComponentLocation();
	const float CapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float ShapeRadius = CapsuleComponent->GetScaledCapsuleRadius() * 0.99f;
	FVector TraceEnd = TraceStart - CapsuleComponent->GetUpVector()* (CapsuleHalfHeight - ShapeRadius + GroundHitToleranceDistance + 1.0f);
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;

#pragma region Standing Check

	UKismetSystemLibrary::SphereTraceSingle(this, TraceStart, TraceEnd, ShapeRadius,
		UEngineTypes::ConvertToTraceType(TraceChannel), true, ActorsToIgnore, DrawDebugType, HitResult, true);
	bIsInAir = !HitResult.bBlockingHit;
	TimeInAir = bIsInAir ? TimeInAir + DeltaTime : 0.0f;
	CurrentStandingSurface = HitResult;

//	VVLOG(Warning, TEXT("TimeInAir = %f"), TimeInAir);

#pragma endregion

#pragma region Update Capsule linearDamping
	/**
	* Update Capsule linearDamping
	* If Grounded L-D is set to 1.0f , in same cases helps to stop the capsule when we are not moving
	* If falling case , stetting L-D to 0.01f , Helps to reach the wanted jump height when JumpImpulse is applied
	*/

	if (CapsuleComponent->GetLinearDamping() != 0.01f && bIsInAir)
	{
		CapsuleComponent->SetLinearDamping(0.01f);
	}
	else if (CapsuleComponent->GetLinearDamping() != 0.5f && !bIsInAir)
	{
		CapsuleComponent->SetLinearDamping(0.5f);
	}
	else if (TimeInAir > 1.0f && !bIsJumping)
	{
		CapsuleComponent->SetLinearDamping(0.5f);
	}
#pragma endregion



	const FVector GravityForce = FVector(0.0f, 0.0f, -1.0f) * GravityPower * GravityScale;
	ApplyGravity(GravityForce, true, true);

}

void UUnitMovementComponent::ApplyGravity(const FVector & Force, bool bAllowSubstepping, bool bAccelChange)
{
	CapsuleComponent->GetBodyInstance()->AddForce(Force, bAllowSubstepping, bAccelChange);
}

void UUnitMovementComponent::DoJump()
{
	if (bIsInAir) { return; }

	const float TargetJumpHeight = JumpHeight + CapsuleComponent->GetScaledCapsuleHalfHeight();
	const FVector JumpImpulse = CapsuleComponent->GetUpVector() * FMath::Sqrt(TargetJumpHeight * 2.0f * GravityPower * GravityScale);

	// use Accelation true??
	CapsuleComponent->GetBodyInstance()->AddImpulse(JumpImpulse, true);
}

void UUnitMovementComponent::DoSprint()
{
	if (bIsInAir || bIsSprinting) { return; }

	LastWalkSpeed = MaxSpeed;
	MaxSpeed *= SpeedBoostMultiplier;
	bIsSprinting = true;
}

void UUnitMovementComponent::DoStopSprint()
{
	MaxSpeed = LastWalkSpeed;
	bIsSprinting = false;
}

void UUnitMovementComponent::StopMovementImmediately()
{
	Super::StopMovementImmediately();

	const FVector ZeroVelocity = FVector(0.0f, 0.0f, 0.0f);
	Velocity = ZeroVelocity;

	if (CapsuleComponent != NULL)
	{
		CapsuleComponent->SetPhysicsLinearVelocity(ZeroVelocity);
	}
}


//capsulehited ÇÔ¼ö¿¡¼­ Ä¸½¶³¢¸® Ãæµ¹ ·ÎÁ÷

bool UUnitMovementComponent::IsMovingOnGround() const
{
	return !bIsInAir;
}

bool UUnitMovementComponent::IsFalling() const
{
	return bIsInAir;
}


bool UUnitMovementComponent::IsSprinting() const
{
	return bIsSprinting;
}

FVector UUnitMovementComponent::GetFallingVelocity() const
{
	return CapsuleComponent->GetComponentVelocity().ProjectOnTo(FVector(0.0f, 0.0f, 1.0f));
}

FVector UUnitMovementComponent::GetMovementVelocity() const
{
	const FVector UpVector = CapsuleComponent ? CapsuleComponent->GetUpVector() : FVector::UpVector;
	return FVector::VectorPlaneProject(Velocity, UpVector);

}

float UUnitMovementComponent::GetCurrentFallingSpeed() const
{
	const float Direction = FVector::DotProduct(FVector(0.0f, 0.0f, 1.0f), GetFallingVelocity());

	return GetFallingVelocity().Size() * FMath::Sign(Direction);
}

float UUnitMovementComponent::GetCurrentWalkSpeed() const
{
	return GetMovementVelocity().Size();
}

float UUnitMovementComponent::GetInAirTime() const
{
	return TimeInAir;
}

bool UUnitMovementComponent::GetbIsInAir() const
{
	return bIsInAir;
}

bool UUnitMovementComponent::GetbIsJumping() const
{
	return bIsJumping;
}

void UUnitMovementComponent::SetbIsJumping(bool bJump)
{
	bIsJumping = bJump;
}
