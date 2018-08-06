// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// grab the controlled tank and double-check it.
	ATank_Pawn* Tank_Holder = GetControlledTank();
	if (Tank_Holder == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AI: %s is not controlling a tank at BeginPlay."), *(GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI is controlling tank: %s"), *(GetControlledTank()->GetName()));
	}
}

ATank_Pawn* ATankAIController::GetControlledTank() {
	return Cast<ATank_Pawn>(GetPawn());
}
