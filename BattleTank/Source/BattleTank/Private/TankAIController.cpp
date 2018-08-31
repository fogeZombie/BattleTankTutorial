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
	ControlledTank = Cast<ATank_Pawn>(GetPawn());
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AI: %s is not controlling a tank at BeginPlay."), *(GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI is controlling tank: %s"), *(ControlledTank->GetName()));
	}

	// find the player's tank
	TargetTank = Cast<ATank_Pawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
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

	// if there is a target tank move towards it and attempt to aim/fire at it's current position
	if (TargetTank != nullptr) {
		MoveToActor(TargetTank, Target_MinDistance);

		ControlledTank->AimAt(TargetTank->GetActorLocation());
		ControlledTank->FireMainWeapon();
	}
}

