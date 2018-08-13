// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{

	float ElevationChange = RelativeSpeed * Elevation_MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp(RawElevation, Elevation_MinElevation, Elevation_MaxElevation);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}


