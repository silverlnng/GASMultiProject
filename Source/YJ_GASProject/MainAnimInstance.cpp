// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComp = OwnerCharacter->GetCharacterMovement();
	}
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		Speed = OwnerCharacter->GetVelocity().Length();

		// 기울어진 정도를 구하기 
		// FRotator Delta = A - B;

		
		FRotator BodyRot = OwnerCharacter->GetActorRotation(); // 현재값으로 갱신
		FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
		BodyPrevRot = BodyRot; // 과거의 값으로 갱신 

		// 순간의 기울어진  Speed
		YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
		UE_LOG(LogTemp, Warning, TEXT("BodyPrevRot:Pitch: %f, Yaw: %f, Roll: %f"), BodyPrevRot.Pitch, BodyPrevRot.Yaw, BodyPrevRot.Roll);
			
		UE_LOG(LogTemp, Warning, TEXT("YawSpeed: %f"),YawSpeed);
		
		// YawSpeed 는 계속해서 새롭게 구해질 것. 
		// 왜 lerp ? 계속해서 변하는 YawSpeed 값에 조금 더 천천히 값을 변하게 하기 위해서 
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);
	}
}

void UMainAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
