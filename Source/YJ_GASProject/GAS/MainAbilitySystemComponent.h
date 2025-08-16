// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MainGameplayAbilityTypes.h"
#include "MainAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API UMainAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void ApplyInitialEffects();
	void GiveInitialAbilities();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<EMainAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

	// BasicAbilities : 게임의 시작부터 모든 플레이어가 기본적으로 가지고있는 능력 .the base abilities will be something that everyone has, like a common basic attack.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<EMainAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
};
