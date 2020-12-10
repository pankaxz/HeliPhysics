// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"

UHeliMainRotor::UHeliMainRotor()
{
	
	PrimaryComponentTick.bCanEverTick = true;
}


void UHeliMainRotor::BeginPlay()
{
	Super::BeginPlay();
	
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
}


void UHeliMainRotor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
}

void UHeliMainRotor::UpdateRotor(float DPS)
{
	// float LocalDPS =( DPS * 0.5f ) * GetWorld()->DeltaTimeSeconds;
	
	if(R22HeliPawn->SC_MainMastRotor)
	{
		R22HeliPawn->SC_MainMastRotor->AddLocalRotation((FRotator(0,(( DPS * MainRotationSpeedModifier ) * GetWorld()->DeltaTimeSeconds),0)));
	}
}

