// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UMainAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	// 매크로 사용
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet,Health,OldValue);
}

void UMainAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet,MaxHealth,OldValue);
}

void UMainAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet,Mana,OldValue);
}

void UMainAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributeSet,MaxMana,OldValue);
}

void UMainAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}
