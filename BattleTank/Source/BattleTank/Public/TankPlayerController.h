// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank_Pawn.h"

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
	ATank_Pawn* GetControlledTank() const;
	
private:
	virtual void BeginPlay() override;

};
