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
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Working")));
	
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
}


void UHeliMainRotor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
}

void UHeliMainRotor::UpdateRotor(float DPS)
{
	float LocalDPS =( DPS * 0.5f );
	
	if(R22HeliPawn->SC_MainMastRotor)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%s"), *R22HeliPawn->SC_MainMastRotor->GetName()));

		//R22HeliPawn->SC_MainMastRotor->AddLocalRotation((FRotator(0,LocalDPS,0)));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
			FString::Printf(TEXT("DPS At Main Rotor %f"), LocalDPS));
		R22HeliPawn->SC_MainMastRotor->AddLocalRotation((FRotator(0,LocalDPS,0)));
		// SC_MainMastRotor not rotating 
	}
}

