// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MainCharacter.h"
#include "InputActionValue.h"
#include "YJ_GASProject/GAS/MainGameplayAbilityTypes.h"
#include "MainPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class YJ_GASPROJECT_API AMainPlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
	
public:
	AMainPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class UCameraComponent* ViewCam;
	
	/*************************************************************/
	/*                           Input                           */
	/*************************************************************/
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpInputAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookInputAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* GameplayInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<EMainAbilityInputID, class UInputAction*> GameplayAbilityInputActions;
	
	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleAbilityInput(const FInputActionValue& InputActionValue, EMainAbilityInputID InputID);
	
	FVector GetLookRightDir() const;
	FVector GetLookFwdDir() const;
	FVector GetMoveFwdDir() const;
};
