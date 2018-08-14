// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"

#include "Engine/World.h"

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

	// Set the barrel reference used by the aiming component
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	// Set the aiming location of the tank with a FVector location
	void AimAt(FVector Location);

	// Fire main weapon
	UFUNCTION(BlueprintCallable, Category = Input)
	void FireMainWeapon();

// fields
public:
	// Specifies the ATankProjectile (or subclass) to use.
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileBlueprint = nullptr;

	// Defines the projectile velocity, which determines how far the tank can fire.
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileVelocity = 4000.0f;

	// Defines the amount of time, in seconds, that it takes the tank to "reload" and be able to fire again.
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;
	float LastFireTime = ReloadTimeInSeconds * -1;
};
