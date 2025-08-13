// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/WidgetComponent.h"
#include "GAS/MainAbilitySystemComponent.h"
#include "GAS/MainAttributeSet.h"
#include "Widget/OverHeadStatsGaugeWidget.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// UAbilitySystemComponent 의 내부작동으로 MAbilitySystemComponent 와 MAttributeSet 가 서로의 존재에 대해 알고있음 . 
	MAbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("MAbility System Component");
	MAttributeSet = CreateDefaultSubobject<UMainAttributeSet>("MAttribute Set");

	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Over Head Widget Component");
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

void AMainCharacter::ServerSideInit()
{
	MAbilitySystemComponent->InitAbilityActorInfo(this, this);
	// 서버에서 만 초기화 작업을 해주고 . 그 초기화 된 변수들은 replicate
	MAbilitySystemComponent->ApplyInitialEffects();
}

void AMainCharacter::ClientSideInit()
{
	MAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

bool AMainCharacter::IsLocallyControlledByPlayer() const
{
	// 리슨서버인 경우 : 서버역할을 하는 클라이언트의 역할

	return GetController() && GetController()->IsLocalController();
	
	return GetLocalRole() == ROLE_AutonomousProxy || GetRemoteRole() == ROLE_AutonomousProxy;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConfigureOverHeadStatusWidget();
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (NewController && !NewController->IsPlayerController()) // 이 경우 AIController 
	{
		// PossessedBy함수는  only called on the server.	
		ServerSideInit();
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return MAbilitySystemComponent;
}

void AMainCharacter::ConfigureOverHeadStatusWidget()
{
	if (!OverHeadWidgetComponent)
	{
		return;
	}
	
	if (IsLocallyControlledByPlayer())
	{
		// 로컬플레이어는 머리위에 위젯이 보 일 필요없음
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	UOverHeadStatsGaugeWidget* OverheadStatsGuage = Cast<UOverHeadStatsGaugeWidget>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverheadStatsGuage)
	{
		OverheadStatsGuage->ConfigureWithASC(GetAbilitySystemComponent());
		OverHeadWidgetComponent->SetHiddenInGame(false);
	}
}

