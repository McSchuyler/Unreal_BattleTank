// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (GetPlayerTank())
	{
		//move towards player
		//aim at player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire if ready
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerPawn) { return nullptr; }
	auto playerTank = Cast<ATank>(playerPawn);

	return playerTank;
}
