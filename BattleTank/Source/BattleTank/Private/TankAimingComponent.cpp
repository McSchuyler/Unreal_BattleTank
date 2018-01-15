// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"


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

void UTankAimingComponent::AimAt(FVector location, float launchSpeed)
{
	if (!barrel) { return; }

	FVector OUT_launchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	//Calculate OUT_launchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT_launchVelocity,
		startLocation,
		location, //end location
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		// Normalize direction vector
		auto aimDirection = OUT_launchVelocity.GetSafeNormal();

		auto ourTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aim at %s"), *ourTankName, *location.ToString());
		//move barrel

		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrelComponent * barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector direction)
{
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = direction.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);
}

