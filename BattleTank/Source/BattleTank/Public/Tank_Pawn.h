// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"

#include "TankBarrel.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank_Pawn.generated.h"

UCLASS()
class BATTLETANK_API ATank_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Set the barrel reference used by the aiming component
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Set the aiming location of the tank with a FVector location
	void AimAt(FVector Location);

	// Fire main weapon
	void FireMain();

// fields
public:
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileVelocity = 50000.0f;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
};
