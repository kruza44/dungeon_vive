// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtoPlayer.h"
#include "UnitStat.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/DataTable.h"
#include "VVGameInstance.h"
#include "VVUnitWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperSpriteComponent.h"
#include "UnitPawnMovementComponent.h"



AProtoPlayer::AProtoPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Box"));
//	FRotator BoxRotation;
//	BoxRotation.Roll = 45.0f;
//	BoxRotation.Pitch = 0.0f;
//	BoxRotation.Yaw = -45.0f;
//	CapsuleComponent->SetWorldRotation(BoxRotation);
	RootComponent = CapsuleComponent;

//	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SPRITE"));
//	SpriteComponent->SetupAttachment(RootComponent);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	CameraArm->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PLAYERCAMERA"));
	PlayerCamera->SetupAttachment(CameraArm);

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(RootComponent);
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

//	auto UnitWidget = LoadObject<UUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/UI_HPBAR.UI_HPBAR'"));
//	VVCHECK(nullptr != UnitWidget);
//	HPBarWidget->SetWidgetClass(UnitWidget->GetClass());
//	HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));

	static ConstructorHelpers::FClassFinder<UVVUnitWidget> UI_HUD(TEXT("/Game/Blueprints/Widgets/UI_HPBAR"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

//	UnitPawnMovement = CreateDefaultSubobject<UUnitPawnMovementComponent>(TEXT("MOVEMENT"));
//	UnitPawnMovement->UpdatedComponent = RootComponent;

//	UDataTable* UnitStatData = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Data/Units.Units'"));
//	VVCHECK(nullptr != UnitStatData);
//	StatDataInDataTable->DataTable = UnitStatData; // Æ¨±è
//	StatDataInDataTable->RowName = TEXT("Human"); //Æ¨±è

}

void AProtoPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UDataTable* UnitStatTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Data/Units.Units'"));
	VVCHECK(nullptr != UnitStatTable);
//	FString UnitDataPath = TEXT("DataTable'/Game/Data/Units.Units'");
//	static ConstructorHelpers::FObjectFinder<UDataTable> DT_UNITDATA(*UnitDataPath);
//	VVCHECK(DT_UNITDATA.Succeeded());
//	UDataTable* UnitStatTable = DT_UNITDATA.Object;
	FVVUnitData* BaseStatData = UnitStatTable->FindRow<FVVUnitData>(TEXT("Human"), TEXT(""));
	VVCHECK(nullptr != BaseStatData);
	UnitStatComponent->SetBaseAndCurrentStat(BaseStatData);
}

void AProtoPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetCameraMode(ECameraMode::PERSPECTIVE);

	auto UnitWidget = Cast<UVVUnitWidget>(HPBarWidget->GetUserWidgetObject());
	VVCHECK(nullptr != UnitWidget);
	if (nullptr != UnitWidget)
	{
		UnitWidget->BindUnitStat(UnitStatComponent);
	}
}

void AProtoPlayer::SetCameraMode(ECameraMode NewCameraMode)
{
	CurrentCameraMode = NewCameraMode;

	switch (CurrentCameraMode)
	{
	case ECameraMode::PERSPECTIVE:
		PlayerCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
		CameraArm->bInheritPitch = true;
		CameraArm->bInheritRoll = true;
		CameraArm->bInheritYaw = true;
		break;
	case ECameraMode::ORTHOGRAPHIC:
		PlayerCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
		PlayerCamera->SetOrthoWidth(800.0f);
		PlayerCamera->SetOrthoNearClipPlane(-800.0f);
		CameraArm->TargetArmLength = 350.0f;
		CameraArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
		CameraArm->bInheritPitch = true;
		CameraArm->bInheritRoll = true;
		CameraArm->bInheritYaw = true;
		break;
	}
}

void AProtoPlayer::CameraSwitch()
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::PERSPECTIVE:
		SetCameraMode(ECameraMode::ORTHOGRAPHIC);
		break;
	case ECameraMode::ORTHOGRAPHIC:
		SetCameraMode(ECameraMode::PERSPECTIVE);
		break;
	}
}

void AProtoPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProtoPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("CameraSwitch"), EInputEvent::IE_Pressed, this, &AProtoPlayer::CameraSwitch);

}

//UPawnMovementComponent* AProtoPlayer::GetMovementComponent() const
//{
//	return UnitPawnMovement;
//}

