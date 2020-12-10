// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliTailRotor.h"
#include "R22Heli_Pawn.h"

// Sets default values for this component's properties
UHeliTailRotor::UHeliTailRotor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UHeliTailRotor::GetTailRotorMaxPitch()
{
	return MaxPitch;
}


// Called when the game starts
void UHeliTailRotor::BeginPlay()
{
	Super::BeginPlay();

	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
	
}


// Called every frame
void UHeliTailRotor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHeliTailRotor::UpdateRotor(float DPS)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Updating Tail Rotor")));
	if(R22HeliPawn->SC_TailMastRotor)
	{
		R22HeliPawn->SC_TailMastRotor->AddLocalRotation((FRotator(0,0	,(( DPS *TailRotationSpeedModifier ) * GetWorld()->DeltaTimeSeconds))));

		if (R22HeliPawn->SM_RTailBlade && R22HeliPawn->SM_LTailBlade)
		{
			R22HeliPawn->SM_LTailBlade->SetRelativeRotation((FRotator(
                0, R22HeliPawn->GetPedalInput() * GetTailRotorMaxPitch() * -1.0 , 0 )));

			R22HeliPawn->SM_RTailBlade->SetRelativeRotation((FRotator(
                0, R22HeliPawn->GetPedalInput() * GetTailRotorMaxPitch() , 0 )));
		}
	}
}


