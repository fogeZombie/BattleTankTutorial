// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATankAIController::ATankAIController() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// grab the controlled tank and double-check it.
	ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AI: %s is not controlling a tank at BeginPlay."), *(GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI is controlling tank: %s"), *(ControlledTank->GetName()));
	}

	// find the player's tank
	TargetTank = GetTargetTank();
	if (TargetTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AI: %s could not locate player tank"), *(GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI located player tank: %s"), *(TargetTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// bail if ControlledTank is nullptr
	if (ControlledTank == nullptr) {
		return;
	}

	// if there is a target tank, aim at it
	if (TargetTank != nullptr) {
		ControlledTank->AimAt(GetTargetTankLocation());
	}
}

ATank_Pawn* ATankAIController::GetControlledTank() const {
	return Cast<ATank_Pawn>(GetPawn());
}

ATank_Pawn* ATankAIController::GetTargetTank() const {
	return Cast<ATank_Pawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

FVector ATankAIController::GetTargetTankLocation() const
{
	// bail if there is no target
	if (TargetTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AI: %s does not have TargetTank."), *(GetName()));
		return FVector(0);
	}

	return TargetTank->GetActorLocation();
}
