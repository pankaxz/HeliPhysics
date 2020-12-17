// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliCharacteristics.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"

UHeliCharacteristics::UHeliCharacteristics()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliCharacteristics::UpdateCharacteristics(AR22Heli_Pawn* R22Heli_Pawn)
{
	HandleLift(R22Heli_Pawn);
	HandleCyclic(R22Heli_Pawn);
	HandlePedals(R22Heli_Pawn);

	myActorQuat= GetOwner()->GetActorQuat();
}


void UHeliCharacteristics::BeginPlay()
{
	Super::BeginPlay();

	HeliMainRotor = GetOwner()->FindComponentByClass<UHeliMainRotor>();
	
	
}



void UHeliCharacteristics::HandleLift(AR22Heli_Pawn* R22Heli_Pawn)
{
	//todo : LIFT FORCE IS SKETCHY..COME BACK AGAIN
	
	FVector LiftForce = R22Heli_Pawn->GetActorUpVector() * (FMath::Abs(GetWorld()->GetGravityZ()) + MaxLiftForce) * 
        R22Heli_Pawn->GetPhysicsFBodyInstance()->GetBodyMass();


	
	float NormalizedRPMs = HeliMainRotor->GetCurrentRPMs()/500.0f;


	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddForce(LiftForce * (FMath::Pow(NormalizedRPMs,2.0f))
                                            * FMath::Pow(R22Heli_Pawn->GetStickyCollectiveInput(), 2.0f),
                                                true, false);
}
/*
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
 //            FString::Printf(TEXT("Lift Force X : %f"),
 //            	(LiftForce.X * R22Heli_Pawn->GetStickyCollectiveInput())));
 //
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
 //        FString::Printf(TEXT("Lift Force Y : %f"),
 //            (LiftForce.Y * R22Heli_Pawn->GetStickyCollectiveInput())));
	//
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
 //        FString::Printf(TEXT("Lift Force Z : %f"),
 //            (LiftForce.Z * R22Heli_Pawn->GetStickyCollectiveInput())));

*/



//Cyclic force is bad
void UHeliCharacteristics::HandleCyclic(AR22Heli_Pawn* R22Heli_Pawn)
{
	
	float CyclicXForce = R22Heli_Pawn->GetCyclicInput().X * CyclicForce;
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((myActorQuat.RotateVector(FVector::ForwardVector)* CyclicXForce),true, true);

	float CyclicYForce = R22Heli_Pawn->GetCyclicInput().Y * CyclicForce;
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((myActorQuat.RotateVector(FVector::RightVector)* CyclicXForce),true, true);
}

void UHeliCharacteristics::HandlePedals(AR22Heli_Pawn* R22Heli_Pawn)
{
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians(FVector(0,0,R22Heli_Pawn->GetPedalInput() * TailForce),
		true, true);
}


// Called every frame
void UHeliCharacteristics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

