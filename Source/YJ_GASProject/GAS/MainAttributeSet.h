// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MainAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API UMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxMana)
private:
	UPROPERTY()
	FGameplayAttributeData Health;
	
	UPROPERTY()
	FGameplayAttributeData MaxHealth;

	UPROPERTY()
	FGameplayAttributeData Mana;
	
	UPROPERTY()
	FGameplayAttributeData MaxMana;
};
