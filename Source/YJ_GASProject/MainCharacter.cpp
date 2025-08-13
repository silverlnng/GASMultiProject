// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/WidgetComponent.h"
#include "GAS/MainAbilitySystemComponent.h"
#include "GAS/MainAttributeSet.h"
#include "Kismet/GameplayStatics.h"
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
	MAbilitySystemComponent->GiveInitialAbilities();
}

void AMainCharacter::ClientSideInit()
{
	MAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

bool AMainCharacter::IsLocallyControlledByPlayer() const
{
	// 리슨서버인 경우 : 서버역할을 하는 클라이언트의 역할

	return GetController() && GetController()->IsLocalController();
	
	// return GetLocalRole() == ROLE_AutonomousProxy || GetRemoteRole() == ROLE_AutonomousProxy;
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

	// 로컬플레이어 외 플레이어 쪽에서 작동시키는 내용들 
	
	UOverHeadStatsGaugeWidget* OverheadStatsGuage = Cast<UOverHeadStatsGaugeWidget>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverheadStatsGuage)
	{
		OverheadStatsGuage->ConfigureWithASC(GetAbilitySystemComponent());
		OverHeadWidgetComponent->SetHiddenInGame(false);

		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
		GetWorldTimerManager().SetTimer(HeadStatGaugeVisibilityUpdateTimerHandle, this, &AMainCharacter::UpdateHeadGaugeVisibility, HeadStatGaugeVisiblityCheckUpdateGap, true);
	}
}

void AMainCharacter::UpdateHeadGaugeVisibility()
{
	// 로컬플레이어 외 다른플레이어가 작동시킬 함수
	// 로컬플레이어를 찾아서 자신과의 거리비교. 
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (LocalPlayerPawn)
	{
		float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		OverHeadWidgetComponent->SetHiddenInGame(DistSquared > HeadStatGaugeVisiblityRangeSquared);
	}
}

