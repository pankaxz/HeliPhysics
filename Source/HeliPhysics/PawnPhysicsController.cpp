// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnPhysicsController.h"
#include "R22Heli_Pawn.h"

UPawnPhysicsController::UPawnPhysicsController()
{

	PrimaryComponentTick.bCanEverTick = true;
	
}


void UPawnPhysicsController::BeginPlay()
{
	Super::BeginPlay();

	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
	HeliCenterOfMass = R22HeliPawn->GetHeliCenterOfMass();
	
	if(R22HeliPawn)
	{
		R22HeliPawn->GetHeliRootBody()->SetMassOverrideInKg(NAME_None, HeliWeight, true);
		
	}
	
}

void UPawnPhysicsController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(R22HeliPawn)
	{
		HandlePhysics();
	}
	
}

void UPawnPhysicsController::HandlePhysics()
{
	
}
