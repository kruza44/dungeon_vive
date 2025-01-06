// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTrailEffect.h"

// Sets default values
AAttackTrailEffect::AAttackTrailEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultSceneRoot;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
	SkeletalMesh->SetupAttachment(RootComponent);

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	TrailParticle->SetupAttachment(SkeletalMesh);

	DelayTime = 0.5f;
	PlayRate = 1.0f;
	FirstSocketName = FName(TEXT("Trail_Start"));
	SecondSocketName = FName(TEXT("Trail_End"));
	LifeTimeName = FName(TEXT("Life_Time"));
	
}


void AAttackTrailEffect::DoAttack_Implementation()
{
}

// Called when the game starts or when spawned
void AAttackTrailEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackTrailEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

