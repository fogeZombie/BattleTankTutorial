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

void UTankAimingComponent::AimAt(FVector Location, float Velocity)
{
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
		UE_LOG(LogTemp, Warning, TEXT("%.2f TAC: %s's aiming at: %s"), GetWorld()->GetTimeSeconds(), *(GetOwner()->GetName()), *(AimDirection.ToString()));

		// aiming the barrel
		FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
		FRotator AimAsRotator = AimDirection.Rotation();
		FRotator DeltaRotator = AimAsRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
	}
}

void UTankAimingComponent::FireMain()
{
	// bail if there is no barrel
	if (Barrel == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TAC: %s's aiming component has no barrel."), *(GetOwner()->GetName()));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("TAC: %s FIRING at: %s"), *(GetOwner()->GetName()), *(AimDirection.ToString()));
	//UE_LOG(LogTemp, Warning, TEXT("TAC: SuggestedVelocity: %s"), *(OutVector.ToString()));
}

