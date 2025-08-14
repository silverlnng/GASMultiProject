// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MainAbilitySystemStatics.generated.h"
/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API UMainAbilitySystemStatics
{
	GENERATED_BODY()
public:
	// 함수호출로 하는 이유 => 필요할때 초기화하고 호출이 되도록 만들기 위해 !
	// static 선언
	static FGameplayTag GetBasicAttackAbilityTag();
};
