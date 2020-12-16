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

	if(HeliMainRotor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
    FString::Printf(TEXT("YAYYYY")));
	}

	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
    FString::Printf(TEXT("NOOO")));
	

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
            FString::Printf(TEXT("Lift Force X : %f"),
            	(LiftForce.X * R22Heli_Pawn->GetStickyCollectiveInput())));

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
        FString::Printf(TEXT("Lift Force Y : %f"),
            (LiftForce.Y * R22Heli_Pawn->GetStickyCollectiveInput())));
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
        FString::Printf(TEXT("Lift Force Z : %f"),
            (LiftForce.Z * R22Heli_Pawn->GetStickyCollectiveInput())));


/*	
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
	// 	FString::Printf(TEXT("Weight in KG : %f"), R22Heli_Pawn->GetHeliRootBody()->GetBodyInstance()->GetBodyMass()));
 //
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
	// 	FString::Printf(TEXT("Lift Force : %f  ,   %f ,  %f"),LiftForce.X, LiftForce.Y, LiftForce.Z));
 //
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
 //        FString::Printf(TEXT("Lift Force size : %f"),LiftForce.Size()));
*/
}

void UHeliCharacteristics::HandleCyclic(AR22Heli_Pawn* R22Heli_Pawn)
{
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
 //    FString::Printf(TEXT("Handleing Cyclic")));
}

void UHeliCharacteristics::HandlePedals(AR22Heli_Pawn* R22Heli_Pawn)
{
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
 //    FString::Printf(TEXT("Handleing pedals")));
}


// Called every frame
void UHeliCharacteristics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

