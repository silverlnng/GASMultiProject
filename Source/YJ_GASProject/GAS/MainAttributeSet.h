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
	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;
private:
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

	// 이게 call 될때, 서버는 이미 값이 변경된 상태
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
};
