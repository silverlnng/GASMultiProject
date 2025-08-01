// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "MainPlayerCharacter.h"

void AMainPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	MPlayerCharacter = Cast<AMainPlayerCharacter>(NewPawn);
	if (MPlayerCharacter)
	{
		MPlayerCharacter->ServerSideInit();
	}
}

void AMainPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	MPlayerCharacter = Cast<AMainPlayerCharacter>(NewPawn);
	if (MPlayerCharacter)
	{
		MPlayerCharacter->ClientSideInit();
	}
}
