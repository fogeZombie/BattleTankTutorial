// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (LeftTrackToSet == nullptr || RightTrackToSet == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent: Initialize - TankTrack is nullptr."));
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->ApplyForce_Forward(Throw);
	RightTrack->ApplyForce_Forward(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	LeftTrack->ApplyForce_Forward(Throw);
	RightTrack->ApplyForce_Forward(Throw * -1.0f);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Not calling Super::RequestDirectMove, completely replacing function.
	FVector NormalizedForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector NormalizedRight = GetOwner()->GetActorRightVector().GetSafeNormal();
	FVector NormalizedDesired = MoveVelocity.GetSafeNormal();

	// Send deltas to IntendMove directions
	IntendMoveForward(FVector::DotProduct(NormalizedForward, NormalizedDesired));
	//IntendMoveRight(FVector::DotProduct(NormalizedRight, NormalizedDesired));
	IntendMoveRight(FVector::CrossProduct(NormalizedForward, NormalizedDesired).Z);
}
