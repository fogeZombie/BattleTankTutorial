// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
* Holds barrel's properties and elevate method.
* Used exclusively as a tank component.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Lighting", "Rendering"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

// fields
private:
	// Elevation movement speed in degrees per second.
	UPROPERTY(EditAnywhere, Category = Movement)
	float Elevation_MaxDegreesPerSecond = 8.0f;

	// Minimum allowed elevation in degrees.
	UPROPERTY(EditAnywhere, Category = Movement)
	float Elevation_MinElevation = 0.0f;
	// Maximum allowed elevation in degrees.
	UPROPERTY(EditAnywhere, Category = Movement)
	float Elevation_MaxElevation = 40.0f;
};
