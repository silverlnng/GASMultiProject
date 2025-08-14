// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAbilitySystemStatics.h"

FGameplayTag UMainAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	// RequestGameplayTag 함수안에 InitializeManager 가 있음
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack");
}
