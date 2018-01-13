// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float deltatime) override;

private:
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& OUT_HitLocation) const;
	bool GetCameraLookDirection(FVector2D screenLocation, FVector& cameraWorldDirection) const;
	bool GetLookVectorHitLocation(FVector,FVector&) const;

	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
	float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float crosshairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;


};
