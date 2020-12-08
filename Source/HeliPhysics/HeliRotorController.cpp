// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliRotorController.h"
#include "HeliRotorInterface.h"
#include "R22Heli_Pawn.h"


UHeliRotorController::UHeliRotorController()
{

	PrimaryComponentTick.bCanEverTick = true;
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
}

void UHeliRotorController::BeginPlay()
{
	Super::BeginPlay();
	
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
	if(RotorsList.Num()>0)
	{
		for(auto Rotor : RotorsList)
		{
			if (IHeliRotorInterface* HeliRotorInterface = Cast<IHeliRotorInterface>(Rotor))
			{ 
				HeliRotorInterface->UpdateRotor();
			} 
		}
	}
}