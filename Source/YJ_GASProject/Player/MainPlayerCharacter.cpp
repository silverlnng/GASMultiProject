// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMainPlayerCharacter::AMainPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());
	
	// 카메라가 Control 의 회전값을 받도록
	CameraBoom->bUsePawnControlRotation = true;

	ViewCam = CreateDefaultSubobject<UCameraComponent>("View Cam");
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// bUseControllerRotationYaw =true 로 하면 실제 로 캐릭터Yaw 도 회전을 함
	bUseControllerRotationYaw = false;

	// 가려는 방향으로 캐릭터가 회전하게 함
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 얼마나 빠르게 회전할지 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

void AMainPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	// PawnClientRestart 를 하는 이유 : 네트워크 플레이어 Pawn 을 클라이언트 측에서 재시작할때 호출되는 함수
	// 새로운 controller 에 possess 되었을때 자동으로 호출되는 함수
	// 서버가 pawn 을 교체하거나 , 새로 스폰했을때 클라이언트쪽 pawn 도 동기화가 되면서 이함수를 실행
	// 클라이언트 측에서 pawn 의 상태를 다시 초기화 하기 위해 사용
	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}
}

void AMainPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Jump);
		EnhancedInputComp->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::HandleLookInput);
		EnhancedInputComp->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::HandleMoveInput);

		for (const TPair<EMainAbilityInputID, UInputAction*>& InputActionPair : GameplayAbilityInputActions)
		{
			// Value : InputAction 이 들어올때 AMainPlayerCharacter::HandleAbilityInput 함수를 실행하면서 Key : EMainAbilityInputID 도 전달
			EnhancedInputComp->BindAction(InputActionPair.Value, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::HandleAbilityInput, InputActionPair.Key);
		}
		
	}
}

void AMainPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();

	// AddController 에게 값을 주는 것. 그래서 CameraBoom 이 controller 의 회전값을 받는것
	AddControllerPitchInput(-InputVal.Y);
	AddControllerYawInput(InputVal.X);
}

void AMainPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();
	InputVal.Normalize();
	
	AddMovementInput(GetMoveFwdDir()*InputVal.Y + GetLookRightDir() * InputVal.X);
}

void AMainPlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue, EMainAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)InputID);
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)InputID);
	}
}

FVector AMainPlayerCharacter::GetLookRightDir() const
{
	// 카메라를 기준으로 움직일려는방향을 구하기 
	return ViewCam->GetRightVector();
}

FVector AMainPlayerCharacter::GetLookFwdDir() const
{
	// 카메라를 기준으로 움직일려는방향을 구하기 
	return ViewCam->GetForwardVector();
}

FVector AMainPlayerCharacter::GetMoveFwdDir() const
{
	// Z 축에 대한 정보는 사용안함
	// CrossProduct : 외적
	// 월드의 UP 방향과 외적으로 , 카메라가 아래 땅을 보고있어도 월드 UP과 수직인 앞방향이 구해진다.
	// 결과적으로 "카메라기준"으로 Forward 방향을 구함
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}
