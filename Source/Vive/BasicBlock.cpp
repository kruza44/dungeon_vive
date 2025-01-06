// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicBlock.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABasicBlock::ABasicBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CUBE"));
	RootComponent = Cube;
}

// Called when the game starts or when spawned
void ABasicBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

