// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::ApplyForce_Forward(float Force)
{
	FVector DesiredForce = GetForwardVector() * Force * Movement_ForceForward_Max;
	UE_LOG(LogTemp, Warning, TEXT("%s applying FORWARD force: %.2f - %s"), *(GetOwner()->GetName()), Force, *(DesiredForce.ToCompactString()));
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(DesiredForce, ForceLocation);
}

void UTankTrack::ApplyForce_Backward(float Force)
{
	FVector DesiredForce = GetForwardVector() * ((Force * Movement_ForceForward_Max) * -1);
	UE_LOG(LogTemp, Warning, TEXT("%s applying BACKWARD force: %.2f - %s"), *(GetOwner()->GetName()), Force, *(DesiredForce.ToCompactString()));

	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(DesiredForce, ForceLocation);
}
