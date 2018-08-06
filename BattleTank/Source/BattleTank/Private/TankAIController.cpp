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
		UE_LOG(LogTemp, Warning, TEXT("AI is controlling tank: %s"), *(Tank_Holder->GetName()));
	}

	// find the player's tank
	ATank_Pawn* Target_Tank = GetTargetTank();
	if (Target_Tank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AI: %s could not locate player tank"), *(GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI located player tank: %s"), *(Target_Tank->GetName()));
	}
}

ATank_Pawn* ATankAIController::GetControlledTank() const {
	return Cast<ATank_Pawn>(GetPawn());
}

ATank_Pawn* ATankAIController::GetTargetTank() const {
	return Cast<ATank_Pawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
