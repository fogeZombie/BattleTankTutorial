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

// Set local barrel reference and pass on to the TankAimingComponent
void ATank_Pawn::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank_Pawn::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank_Pawn::AimAt(FVector Location)
{
	TankAimingComponent->AimAt(Location, ProjectileVelocity);
}

void ATank_Pawn::FireMainWeapon()
{
	// bail if there isn't a barrel
	if (Barrel == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TAC: %s has not set a barrel reference."), *(GetOwner()->GetName()));
		return;
	}

	FVector SpawnLocation = Barrel->GetSocketLocation(FName("ProjectileLaunchLocation"));
	FRotator SpawnRotation = Barrel->GetSocketRotation(FName("ProjectileLaunchLocation"));
	ATankProjectile* Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);

	Projectile->LaunchProjectile(ProjectileVelocity);
}

