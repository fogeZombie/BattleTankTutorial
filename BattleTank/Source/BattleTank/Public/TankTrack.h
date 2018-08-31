// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Specialized tank track that handles basic tank movement.
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent), hidecategories = ("Lighting", "Rendering"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ApplyForce_Forward(float Force);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ApplyForce_Right(float Force);

// fields
private:
	// Force to apply to the track, in newtons.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Movement_ForceForward_Max = 4000000.0f;

	// Force to apply to the track, in newtons.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Movement_ForceBackward_Max = 2000000.0f;

	// Force to apply to the track, in newtons.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Movement_ForceRight_Max = 2000000.0f;
};
