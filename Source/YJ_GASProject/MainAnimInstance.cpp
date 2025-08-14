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
		FRotator BodyRot = OwnerCharacter->GetActorRotation();
		FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
		BodyPrevRot = BodyRot;

		YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);
	}
}

void UMainAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
