// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	class UGuageWidget* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UGuageWidget* ManaBar;

	UPROPERTY()
	class UAbilitySystemComponent* OwnerAbilitySystemComponent;
};