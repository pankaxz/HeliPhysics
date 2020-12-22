// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliCharacteristics.h"

#include "DrawDebugHelpers.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"
#include "Components/ArrowComponent.h"

UHeliCharacteristics::UHeliCharacteristics()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliCharacteristics::UpdateCharacteristics(AR22Heli_Pawn* R22Heli_Pawn)
{
	HandleLift(R22Heli_Pawn);
	HandleCyclic(R22Heli_Pawn);
	HandlePedals(R22Heli_Pawn);

	CalculateLevel(R22Heli_Pawn);
	
	AutoLevel(R22Heli_Pawn);

	myActorQuat= GetOwner()->GetActorQuat();
}


void UHeliCharacteristics::BeginPlay()
{
	Super::BeginPlay();

	HeliMainRotor = GetOwner()->FindComponentByClass<UHeliMainRotor>();
	
	
}



void UHeliCharacteristics::HandleLift(AR22Heli_Pawn* R22Heli_Pawn)
{
	
	FVector LiftForce = R22Heli_Pawn->GetActorUpVector() * (FMath::Abs(GetWorld()->GetGravityZ()) + MaxLiftForce) * 
        R22Heli_Pawn->GetPhysicsFBodyInstance()->GetBodyMass();

	
	float NormalizedRPMs = HeliMainRotor->GetCurrentRPMs()/500.0f;

	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddForce(LiftForce * (FMath::Pow(NormalizedRPMs,2.0f))
                                            * FMath::Pow(R22Heli_Pawn->GetStickyCollectiveInput(), 2.0f),
                                                true, false);
}

//Cyclic force is bad
void UHeliCharacteristics::HandleCyclic(AR22Heli_Pawn* R22Heli_Pawn)
{

	float CyclicXForce = R22Heli_Pawn->GetCyclicInput().X * CyclicForce;
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((myActorQuat.RotateVector(FVector::ForwardVector)* CyclicXForce),
		true, true);

	
	float CyclicYForce = R22Heli_Pawn->GetCyclicInput().Y * CyclicForce;
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((myActorQuat.RotateVector(FVector::RightVector)* CyclicYForce),
		true, true);

	
	FVector ForwardVec = FlatFwd.Vector() * FwdDot;
	FVector RightVec = FlatRight.Vector() * RightDot;

	FVector TempCylicDirection = ForwardVec + RightVec;
	FVector FinalCylicDirection = TempCylicDirection.GetClampedToSize(-1,1) * (CyclicForce * CyclicForceMultiplier);

	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddForce(FinalCylicDirection, true, false);
}

void UHeliCharacteristics::HandlePedals(AR22Heli_Pawn* R22Heli_Pawn)
{
	if(R22Heli_Pawn->GetPedalInput())
	{
		R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians(FVector(0,0,R22Heli_Pawn->GetPedalInput() * TailForce),
        true, true);
	}

}

//todo:: Debug line not working
void UHeliCharacteristics::CalculateLevel(AR22Heli_Pawn* R22Heli_Pawn)
{
	//calculate the flat forward
    FlatFwd = R22Heli_Pawn->GetActorForwardVector().Rotation();
    FlatFwd.Pitch = 0.0f;
	FlatFwd.Normalize();
	R22Heli_Pawn->ForwardArrow->SetWorldRotation(FRotator(FlatFwd));	

	//calculate flat right
	FlatRight = R22Heli_Pawn->GetActorRightVector().Rotation();
	FlatRight.Pitch = 0.0f;
	FlatRight.Normalize();
	R22Heli_Pawn->RightArrow->SetWorldRotation(FRotator(FlatRight));

	
	//calculate angles
	FwdDot = FVector::DotProduct(R22Heli_Pawn->GetActorUpVector(), FlatFwd.Vector());
	RightDot = FVector::DotProduct(R22Heli_Pawn->GetActorUpVector(), FlatRight.Vector());

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
		FString::Printf(TEXT("Forward Dot %f"), FwdDot));

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
		FString::Printf(TEXT("Right Dot %f"), RightDot));
	
}

void UHeliCharacteristics::AutoLevel(AR22Heli_Pawn* R22Heli_Pawn)
{
	float RightForce = -FwdDot * AutoLevelForce;
	float ForwardForce = RightDot * AutoLevelForce;

	//Todo :: auto levelling adding delta to the rotaion
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((myActorQuat.RotateVector(FVector::ForwardVector) * ForwardForce),
        true, true);

	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((myActorQuat.RotateVector(FVector::RightVector) * RightForce),
        true, true);

}


// Called every frame
void UHeliCharacteristics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

