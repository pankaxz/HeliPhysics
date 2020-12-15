// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliCharacteristics.h"
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

}

//Todo : Force working weird. Mass is not getting registered via code
void UHeliCharacteristics::HandleLift(AR22Heli_Pawn* R22Heli_Pawn)
{
	//todo : dix the weight.
	
	FVector LiftForce = R22Heli_Pawn->GetActorUpVector() * -1.0 * GetWorld()->GetGravityZ() * (1200 + 0.005);
		// R22Heli_Pawn->GetPhysicsFBodyInstance()->GetBodyMass();//
	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddForce(LiftForce, true, false);



	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
		FString::Printf(TEXT("Weight in KG : %f"), R22Heli_Pawn->GetHeliRootBody()->GetBodyInstance()->GetBodyMass()));
 
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
		FString::Printf(TEXT("Lift Force : %f  ,   %f ,  %f"),LiftForce.X, LiftForce.Y, LiftForce.Z));
 
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
        FString::Printf(TEXT("Lift Force size : %f"),LiftForce.Size()));

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

