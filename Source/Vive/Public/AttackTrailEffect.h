// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vive.h"
#include "GameFramework/Actor.h"
#include "AttackTrailEffect.generated.h"

UCLASS(Blueprintable)
class VIVE_API AAttackTrailEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackTrailEffect();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	UCurveFloat* CurveVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	UAnimSequence* AnimVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	UParticleSystem* ParticleVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	bool IsLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	bool IsTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	float PlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	float TimeVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	float TrailLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	FName FirstSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	FName SecondSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrailEffect)
	FName LifeTimeName;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AttackEvent")
	void DoAttack();
	virtual void DoAttack_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
