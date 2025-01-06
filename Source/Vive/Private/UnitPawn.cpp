// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitPawn.h"
#include "UnitStat.h"

// Sets default values
AUnitPawn::AUnitPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UnitStatComponent = CreateDefaultSubobject<UUnitStat>(TEXT("UNITSTAT"));
}

// Called when the game starts or when spawned
void AUnitPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

float AUnitPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// 데미지 (방어력 등 고려) 계산식

	UnitStatComponent->SetHPDamage(FinalDamage);
	VVLOG(Warning, TEXT("Got Damage: %f"), FinalDamage);
	return FinalDamage;
}

// Called every frame
void AUnitPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitPawn::CauseDamage_Implementation(float BaseDamage, float PoiseDamage, float PushPower, FVector PushDirection, FVector HitFromDirection, AActor* DamageCauser, AController* DamageInstigator)
{
	// 나중에 UnitStat 기반 데미지 계산 함수 구현
	float FinalDamage = BaseDamage;

	UnitStatComponent->SetHPDamage(FinalDamage);
}