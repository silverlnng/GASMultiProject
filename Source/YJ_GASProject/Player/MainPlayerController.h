// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// 오직 서버에서만 작동
	void OnPossess(APawn* NewPawn) override;

	// 오직 클라이언트 쪽에서만 작동 + 리슨서버인경우 작동 (리슨서버 :클라이언트가 서버이자 클라이언트 역할)
	void AcknowledgePossession(APawn* NewPawn) override;
private:
	UPROPERTY()
	class AMainPlayerCharacter* MPlayerCharacter;

	void SpawnGameplayWidget();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UGameplayWidget> GameplayWidgetClass;

	UPROPERTY()
	class UGameplayWidget* GameplayWidget;
};
