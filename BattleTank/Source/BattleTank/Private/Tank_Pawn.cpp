// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Pawn.h"

// Sets default values
ATank_Pawn::ATank_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");
}

// Called when the game starts or when spawned
void ATank_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank_Pawn::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank_Pawn::AimAt(FVector Location)
{
	TankAimingComponent->AimAt(Location, ProjectileVelocity);
}

void ATank_Pawn::FireMain()
{
	TankAimingComponent->FireMain();
}

