// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCreatureOne.h"
#include "UnitStat.h"
#include "Engine/DataTable.h"
#include "Components/WidgetComponent.h"
#include "VVUnitWidget.h"
#include "VVGameInstance.h"

ATestCreatureOne::ATestCreatureOne()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleCollision;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(RootComponent);
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UVVUnitWidget> UI_HUD(TEXT("/Game/Blueprints/Widgets/UI_HPBAR"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
}

void ATestCreatureOne::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UDataTable* UnitStatTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Data/Units.Units'"));
	VVCHECK(nullptr != UnitStatTable);

	FVVUnitData* BaseStatData = UnitStatTable->FindRow<FVVUnitData>(TEXT("TestCreature"), TEXT(""));
	VVCHECK(nullptr != BaseStatData);
	UnitStatComponent->SetBaseAndCurrentStat(BaseStatData);
}

void ATestCreatureOne::BeginPlay()
{
	Super::BeginPlay();

	auto UnitWidget = Cast<UVVUnitWidget>(HPBarWidget->GetUserWidgetObject());
	VVCHECK(nullptr != UnitWidget);
	if (nullptr != UnitWidget)
	{
		UnitWidget->BindUnitStat(UnitStatComponent);
	}
}
