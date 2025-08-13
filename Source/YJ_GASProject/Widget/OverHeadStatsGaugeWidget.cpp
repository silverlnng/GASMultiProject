// Fill out your copyright notice in the Description page of Project Settings.


#include "OverHeadStatsGaugeWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GuageWidget.h"
#include "YJ_GASProject/GAS/MainAttributeSet.h"

void UOverHeadStatsGaugeWidget::ConfigureWithASC(class UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilitySystemComponent)
	{
		HealthBar->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UMainAttributeSet::GetHealthAttribute(), UMainAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UMainAttributeSet::GetManaAttribute(), UMainAttributeSet::GetMaxManaAttribute());
	}
}
