// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliRotorController.h"
#include "HeliRotorInterface.h"
#include "R22Heli_Pawn.h"


UHeliRotorController::UHeliRotorController()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliRotorController::BeginPlay()
{
	Super::BeginPlay();
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
	
	for(UActorComponent* Component : R22HeliPawn->HeliActorComponents)
	{
		if(Component)
		{
			if(Component->GetClass()->ImplementsInterface(UHeliRotorInterface::StaticClass()))
			{
				RotorsList.Add(Component);
			}
		}
	}
}


void UHeliRotorController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHeliRotorController::UpdateRotors(float CurrentRPM)
{
	//Degree per second calculation
	float DPS = (CurrentRPM * 360)/60.0f;
	DPS = FMath::Clamp(DPS, 0.0f, MaxDPS); 

	//Update Rotors
	if(RotorsList.Num()>0)
	{
		for(auto Rotor : RotorsList)
		{
			if (IHeliRotorInterface* HeliRotorInterface = Cast<IHeliRotorInterface>(Rotor))
			{ 
				HeliRotorInterface->UpdateRotor(DPS);
			} 
		}
	}
}