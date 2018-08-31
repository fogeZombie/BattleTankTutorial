// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::ApplyForce_Forward(float Force)
{
	FVector DesiredForce; // Calculated force to apply to the "track"
	FVector ForceLocation = GetComponentLocation();

	// handle forward
	if (Force > 0) {
		DesiredForce = GetForwardVector() * Force * Movement_ForceForward_Max;
	}
	// handle backward
	else {
		DesiredForce = GetForwardVector() * Force * Movement_ForceBackward_Max;
	}

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(DesiredForce, ForceLocation);
}

// For "hover"-style tank movement
void UTankTrack::ApplyForce_Right(float Force)
{
	FVector ForceLocation = GetComponentLocation();
	FVector DesiredForce = GetRightVector() * Force * Movement_ForceForward_Max;

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(DesiredForce, ForceLocation);
}

