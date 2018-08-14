// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
* Holds tank turret properties and rotate method.
* Exclusively used as a tank component.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Physics", "Collision", "Lighting", "Rendering"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);

// fields
private:
	// Elevation movement speed in degrees per second.
	UPROPERTY(EditAnywhere, Category = Movement)
	float Rotation_MaxDegreesPerSecond = 32.0f;
};
