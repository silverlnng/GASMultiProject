// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAbilitySystemComponent.h"

void UMainAbilitySystemComponent::ApplyInitialEffects()
{

	// 초기화 부분은 서버에서 만 실행되어야함 . HasAuthority 으로 서버인지 체크
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		// ApplyGameplayEffectToSelf()
	}
}

