// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"


void UTankBarrelComponent::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);

	auto elevationChange = relativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;

	auto elevation = FMath::Clamp(rawNewElevation, minElevationDegree, maxElevationDegree);

	SetRelativeRotation(FRotator(rawNewElevation, 0.0f, 0.0f));
}

