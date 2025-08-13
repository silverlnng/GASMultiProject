// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"
#include "GuageWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "YJ_GASProject/GAS/MainAttributeSet.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	
	if (OwnerAbilitySystemComponent)
	{
		HealthBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComponent, UMainAttributeSet::GetHealthAttribute(), UMainAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComponent, UMainAttributeSet::GetManaAttribute(), UMainAttributeSet::GetMaxManaAttribute());
	}
}
