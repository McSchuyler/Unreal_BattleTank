// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATankPlayerController::Tick(float deltatime)
{
	Super::Tick(deltatime);
	AimTowardsCrosshair();
	
}

//Get pawn of the player controlled tank
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Get camera direction corresponding to crosshair screen location
bool ATankPlayerController::GetCameraLookDirection(FVector2D screenLocation, FVector& cameraWorldDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, cameraWorldDirection);
}

//Raycast a line. If line hit the landscape, return true. Get hit location
bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT_HitLocation) const
{
	int32 viewportSizeX;
	int32 viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	//calculate actual crosshair location in pixel
	auto screenLocation = FVector2D(crosshairXLocation,crosshairYLocation);

	//Get location hit by line trace with camera direction coressponding to the crosshair
	FVector cameraWorldDirection;
	if (GetCameraLookDirection(screenLocation, cameraWorldDirection))
	{
		GetLookVectorHitLocation(cameraWorldDirection, OUT_HitLocation);
	}

	return true;
}

//Get location where the line trace is hit
bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& OUT_hitLocation) const
{
	FHitResult hit;
	auto cameraLocation = PlayerCameraManager->GetCameraLocation();
	auto lineTraceEndLocation = cameraLocation + (lookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		hit,
		cameraLocation,
		lineTraceEndLocation,
		ECollisionChannel::ECC_Visibility
		))
	{
		OUT_hitLocation = hit.Location;

		return true;
	}

	return false;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector hitLocation; //OUT parameter
	
	if (GetSightRayHitLocation(hitLocation))
	{
		//tell controlled tank to aim at hit location
		UE_LOG(LogTemp, Warning, TEXT("Hit Location : %s"), *hitLocation.ToString());
	}
}



