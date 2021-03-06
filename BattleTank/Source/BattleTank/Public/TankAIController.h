// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank_Pawn.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	ATank_Pawn* ControlledTank = nullptr;
	ATank_Pawn* TargetTank = nullptr;

	UPROPERTY(EditAnywhere, Category = PositioningParameters)
	float Target_MinDistance = 3000.0f;
};
