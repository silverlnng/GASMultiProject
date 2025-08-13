// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadStatsGaugeWidget.generated.h"

/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API UOverHeadStatsGaugeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConfigureWithASC(class UAbilitySystemComponent* AbilitySystemComponent);
private:
	UPROPERTY(meta=(BindWidget))
	class UGuageWidget* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UGuageWidget* ManaBar;
};
