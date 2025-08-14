// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Combo.h"
#include "MainAbilitySystemStatics.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGA_Combo::UGA_Combo()
{
	// 에디터창에서 할당한 태그를 c++ 에서 할당하기 
	AbilityTags.AddTag(UMainAbilitySystemStatics::GetBasicAttackAbilityTag());
	BlockAbilitiesWithTag.AddTag(UMainAbilitySystemStatics::GetBasicAttackAbilityTag());
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	// GameAbility 를 활성화 하기 전에 체크해야하는 것
		// GameAbility 를 활성화하는데 마나를 소모한다 => 마나를 체크
		// GameAbility 를 활성화하는데 쿨타임이 있다 => 쿨타임을 체크
		// CommitAbility 으로 체크 
	
	/*if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// EndAbility 를 꼭 해줘야함
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}*/
	
	if (!K2_CommitAbility()) // CommitAbility 와 동일
	{
		K2_EndAbility();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Casting GA Combo"));

// 오직 서버이거나 실제 수행하는 로컬플레이어인경우 여서 PredictionKey 가 있는 경우 
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		// ability task 를 이용해서 콤보 AnimMontage 를 실행하기
		// 팩토리패턴 비슷. 클래스 인스턴스를 만들어서 리턴
		
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// 애니메이션 이벤트에 함수를 AddDynamic 해주기 .
		
		PlayComboMontageTask->ReadyForActivation();
		// ReadyForActivation : 실제로 생성한 Task 수행하는 함수 . 이걸안하면 그냥 생성만됨 !
	}
}
