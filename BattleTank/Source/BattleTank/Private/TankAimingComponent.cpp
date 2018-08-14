// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector Location, float Velocity)
{
	// bail if there isn't a turret
	if (Turret == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TAC: %s has not set a turret reference."), *(GetOwner()->GetName()));
	}

	// bail if there isn't a barrel
	if (Barrel == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TAC: %s has not set a barrel reference."), *(GetOwner()->GetName()));
	}

	//UE_LOG(LogTemp, Warning, TEXT("TAC: %s is aiming AT: %s FROM: %s"), *(GetOwner()->GetName()), *Location.ToString(), *(Barrel->GetComponentLocation().ToString()));

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileLaunchLocation"));
	bool SolutionFound = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, Location, Velocity, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (SolutionFound == true) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveTurretAndBarrel(FVector AimDirection)
{
	// grab a rotator for the normalized velocity, for use in figuring out elevation and rotation deltas
	FRotator AimAsRotator = AimDirection.Rotation();

	// aiming the turret
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator TurretDeltaRotator = AimAsRotator - TurretRotator;
	Turret->Rotate(TurretDeltaRotator.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("%.2f TAC: %s's yaw: %s"), GetWorld()->GetTimeSeconds(), *(GetOwner()->GetName()), *(TurretDeltaRotator.ToString()));

	// aiming the barrel
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator BarrelDeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(BarrelDeltaRotator.Pitch);
}

void UTankAimingComponent::FireMain()
{
	// bail if there is no turret
	if (Turret == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TAC: %s's aiming component has no turret."), *(GetOwner()->GetName()));
		return;
	}

	// bail if there is no barrel
	if (Barrel == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TAC: %s's aiming component has no barrel."), *(GetOwner()->GetName()));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("TAC: %s FIRING at: %s"), *(GetOwner()->GetName()), *(AimDirection.ToString()));
	//UE_LOG(LogTemp, Warning, TEXT("TAC: SuggestedVelocity: %s"), *(OutVector.ToString()));
}

