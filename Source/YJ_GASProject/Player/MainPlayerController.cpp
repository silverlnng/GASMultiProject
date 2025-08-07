// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "MainPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "YJ_GASProject/Widget/GameplayWidget.h"

void AMainPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	MPlayerCharacter = Cast<AMainPlayerCharacter>(NewPawn);
	if (MPlayerCharacter)
	{
		MPlayerCharacter->ServerSideInit();
	}

	// 서버쪽에서는 최소한 의 논리만 실행되도록
	// ui 같은 많은 에셋 소모하는 것 실행하지 않음
}

void AMainPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	MPlayerCharacter = Cast<AMainPlayerCharacter>(NewPawn);
	if (MPlayerCharacter)
	{
		MPlayerCharacter->ClientSideInit();
		// 위젯생성은 클라이언트 만. 서버에서 할필요없음
		SpawnGameplayWidget();
	}

}

void AMainPlayerController::SpawnGameplayWidget()
{
	// 로컬플레이어만 생성하도록 (서버에서는 모든 PlayerController 다있음) 
	if (!IsLocalPlayerController())
		return;

	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}
