// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	// grab the controlled tank and double-check it.
	ATank_Pawn* Tank_Holder = GetControlledTank();
	if (Tank_Holder == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not controlling a tank at BeginPlay."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *(GetControlledTank()->GetName()));
	}
	
}

ATank_Pawn* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank_Pawn>(GetPawn());
}

