// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	// grab the controlled tank and double-check it.
	ATank_Pawn* Tank_Holder = GetControlledTank();
	if (Tank_Holder == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not controlling a tank at BeginPlay."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *(GetControlledTank()->GetName()));
		ControlledTank = Tank_Holder;
	}

	// bind FireMain to input
	// find/grab attached input component
	InputComponent = FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing Input Component on: %s"), *(GetOwner()->GetName()));
	}
	else {
		InputComponent->BindAction("FireMain", IE_Pressed, this, &ATankPlayerController::FireMain);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardCrosshair();
}

ATank_Pawn* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank_Pawn>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AimTowardCrossHair - ControlledTank is nullptr."));
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation) == true) {
		ControlledTank->AimAt(HitLocation);
	}
}

// returns true if it hits ECC_WorldStatic, populates OutHitLocation if true
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	/// setup for a physics trace from screen space deprojection of HUD element
	// set up the view position based on the viewport
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// de-project viewport screen location to figure out worldspace
	FVector WorldLocation, WorldDirection;
	DeprojectScreenPositionToWorld(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY, WorldLocation, WorldDirection);

	// figure out the endpoint based on AimDistance
	FVector AimDistanceEnd = WorldLocation + (WorldDirection * AimDistance);
	DrawDebugLine(GetWorld(), WorldLocation, AimDistanceEnd, FColor::Blue, false, -1.0f, 0, 1.0f);

	// set up and run the trace, looking for ECC_WorldStatic objects
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, AimDistanceEnd, ECollisionChannel::ECC_Visibility);

	// check if something was hit on the trace, if so populate the location
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *(ActorHit->GetName()));
		OutHitLocation = Hit.Location;
		return true;
	}

	// else
	return false;
}

void ATankPlayerController::FireMain()
{
	ControlledTank->FireMain();
}
