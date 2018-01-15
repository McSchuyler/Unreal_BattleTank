// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
*
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()


public:
	void Elevate(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere)
	float MaxDegreePerSecond = 20.0f;

	UPROPERTY(EditAnywhere)
	float maxElevationDegree = 30.0f;

	UPROPERTY(EditAnywhere)
	float minElevationDegree = 0.0f;
};
