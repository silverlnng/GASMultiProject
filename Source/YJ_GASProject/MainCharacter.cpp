// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "GAS/MainAbilitySystemComponent.h"
#include "GAS/MainAttributeSet.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// UAbilitySystemComponent 의 내부작동으로 MAbilitySystemComponent 와 MAttributeSet 가 서로의 존재에 대해 알고있음 . 
	MAbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("MAbility System Component");
	MAttributeSet = CreateDefaultSubobject<UMainAttributeSet>("MAttribute Set");
}

void AMainCharacter::ServerSideInit()
{
	MAbilitySystemComponent->InitAbilityActorInfo(this, this);
	// 서버에서 만 초기화 작업을 해주고 . 그 초기화 된 변수들은 replicate
	MAbilitySystemComponent->ApplyInitialEffects();
}

void AMainCharacter::ClientSideInit()
{
	MAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return MAbilitySystemComponent;
}

