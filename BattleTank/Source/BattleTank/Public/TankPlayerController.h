// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank_Pawn.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();
	
protected:
	virtual void BeginPlay() override;
	ATank_Pawn* GetControlledTank() const;
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation);

public: 
	virtual void Tick(float DeltaTime) override;

private:
	ATank_Pawn* ControlledTank = nullptr;

	UPROPERTY(EditAnywhere)
	float AimDistance = 10000.0f;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.33f;

	FVector PlayerPosition;
	FRotator PlayerRotation;
	FVector AimDistanceEnd;

};
