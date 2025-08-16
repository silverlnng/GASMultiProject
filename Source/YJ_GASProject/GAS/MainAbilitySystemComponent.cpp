// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAbilitySystemComponent.h"

void UMainAbilitySystemComponent::ApplyInitialEffects()
{

	// 초기화 부분은 서버에서 만 실행되어야함 . HasAuthority 으로 서버인지 체크
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		// UGameplayEffect 들이 UMainAttributeSet 에 있는 Health,Mana 등 속성을 정의하고 있음
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		
		// UMainAttributeSet 값들을 초기화 
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		// ApplyGameplayEffectSpecToSelf 함수와 ApplyGameplayEffectToSelf() 와 차이점 ?
	}
}

void UMainAbilitySystemComponent::GiveInitialAbilities()
{
	// 초기화 부분은 서버에서 만 실행되어야함 . HasAuthority 으로 서버인지 체크
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;


	// Input ID 와 UGameplayAbility 을 대응시킴
	
	for (const TPair<EMainAbilityInputID,TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, (int32)AbilityPair.Key, nullptr));
	}
	
	for (const TPair<EMainAbilityInputID,TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, (int32)AbilityPair.Key, nullptr));
	}

}


