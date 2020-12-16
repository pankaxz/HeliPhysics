// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"

UHeliMainRotor::UHeliMainRotor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


float UHeliMainRotor::GetMainRotorMaxPitch()
{
	return MaxPitch;
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

float UHeliMainRotor::GetCurrentRPMs()
{
	return CurrentRPMs;
}

void UHeliMainRotor::UpdateRotor(float DPS)
{

	if(R22HeliPawn->SC_MainMastRotor)
	{
	
		CurrentRPMs = (DPS / 360) * 60.0f; //
		
		R22HeliPawn->SC_MainMastRotor->AddLocalRotation((FRotator(0,
					(( DPS * MainRotationSpeedModifier) * GetWorld()->DeltaTimeSeconds), 0)));

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
                    FString::Printf(TEXT("DPS : %f"),
                        (DPS * MainRotationSpeedModifier)));


		
		//Pitch Rotation of the main rotor blades
		if (R22HeliPawn->SM_RMainBlade && R22HeliPawn->SM_LMainBlade)
		{
			R22HeliPawn->SM_LMainBlade->SetRelativeRotation((FRotator(
				0, 0 , R22HeliPawn->GetStickyCollectiveInput() * GetMainRotorMaxPitch() )));

			R22HeliPawn->SM_RMainBlade->SetRelativeRotation((FRotator(
				0, 0 , R22HeliPawn->GetStickyCollectiveInput() * GetMainRotorMaxPitch() * -1.0 )));
		}
	}
}


