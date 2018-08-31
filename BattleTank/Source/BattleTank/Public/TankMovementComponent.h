// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankTrack.h"

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Required for tank movement. Responsible for "driving" the tank tracks.
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IntendMoveRight(float Throw);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

// fields
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
