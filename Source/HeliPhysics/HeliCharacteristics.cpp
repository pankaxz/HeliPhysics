// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliCharacteristics.h"

#include "GenericPlatform/GenericPlatformMath.h"
#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

class AR22Heli_Pawn;
UHeliCharacteristics::UHeliCharacteristics()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliCharacteristics::UpdateCharacteristics()
{
	HandleLift();
	HandlePedals();
	HandleCyclic();
	CalculateAngle();
	AutoLevel();

	PawnQuat = R22Heli_Pawn->GetActorQuat();
}


void UHeliCharacteristics::BeginPlay()
{
	Super::BeginPlay();

	R22Heli_Pawn = Cast<AR22Heli_Pawn> (GetOwner());
	HeliMainRotor = GetOwner()->FindComponentByClass<UHeliMainRotor>();
}

void UHeliCharacteristics::HandleLift()
{
	FVector LiftForce;
	float NormalizedRPMs = HeliMainRotor->GetCurrentRPMs()/500.0f;
	IdleForce = (R22Heli_Pawn->GetHeliRootBody()->GetMass() * 980.0f);
	
	if(R22Heli_Pawn->GetRawCollectiveInput() > 0)
	{
		LiftForce = R22Heli_Pawn->GetActorUpVector() *  AscendForce * FMath::Pow( NormalizedRPMs, 2.0);

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
			FString::Printf(TEXT("Ascend Force %f"), LiftForce.Size()));
	}

	if(R22Heli_Pawn->GetRawCollectiveInput() < 0)
	{
		LiftForce = R22Heli_Pawn->GetActorUpVector() * DescentForce ;

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
			FString::Printf(TEXT("Descent Force %f"), LiftForce.Size()));
	}

	if(R22Heli_Pawn->GetRawCollectiveInput() == 0 && NormalizedRPMs > 0)
	{
		LiftForce = R22Heli_Pawn->GetActorUpVector() * DownForce;
		
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
			FString::Printf(TEXT("Down Force %f"), LiftForce.Size()));
	}

	R22Heli_Pawn->GetHeliRootBody()->AddForce( LiftForce * IdleForce , NAME_None, false);
	
}

void UHeliCharacteristics::HandlePedals()
{
	if(R22Heli_Pawn->GetPedalInput())
	{
		R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
            GetRelativeTransform().TransformVector((FVector::UpVector.ZAxisVector))* R22Heli_Pawn->GetPedalInput() * TailForce,
                NAME_None,true);
	}
}


//TODO: Later
///--------------------------------------------------
	//Cyclic force is bad
void UHeliCharacteristics::HandleCyclic()
{
	float CyclicXForce = R22Heli_Pawn->GetCyclicInput().X * CyclicForce;
	float CyclicYForce = R22Heli_Pawn->GetCyclicInput().Y * CyclicForce;

	FVector CyclicHorizontal = (R22Heli_Pawn->GetHeliRootBody()->
    GetRelativeTransform().TransformVector((FVector::ForwardVector)));
	
	FVector CyclicPedal = R22Heli_Pawn->GetHeliRootBody()->
            GetRelativeTransform().TransformVector((FVector::UpVector.ZAxisVector));
	
	FVector CyclicPedalComboForce ;
	
	//also adding some pedal
/*
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector)* CyclicXForce),
		true, true);
	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector)* CyclicYForce),
		true, true);

	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector)* CyclicXForce),
	NAME_None, true);

	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector)* CyclicYForce),
	NAME_None, true);
	*/
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(CyclicHorizontal * CyclicXForce ,NAME_None,true);
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(CyclicPedal * -CyclicXForce * CyclicTailForce , NAME_None,true);

	
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
	GetRelativeTransform().TransformVector((FVector::RightVector) * CyclicYForce )
	,NAME_None,true);

	FVector ForwardVec = FlatFwd.Vector() * FwdDot;
	FVector RightVec = FlatRight.Vector() * RightDot;
	
	FVector FinalCylicDirection = ForwardVec + RightVec * (CyclicForce * CyclicForceMultiplier);
	R22Heli_Pawn->GetHeliRootBody()->AddForce(FinalCylicDirection, NAME_None, true);

}

//todo:: Debug line not working
void UHeliCharacteristics::CalculateAngle()
{	
	/*//old---
	//calculate the flat forward
	FlatFwd = R22Heli_Pawn->GetActorForwardVector().Rotation();
	FlatFwd.Pitch = 0.0f;
	R22Heli_Pawn->ForwardArrow->SetWorldRotation(FRotator(FlatFwd));		

	//calculate flat right
	FlatRight = R22Heli_Pawn->GetActorRightVector().Rotation();
	FlatRight.Pitch = 0.0f;
	R22Heli_Pawn->RightArrow->SetWorldRotation(FRotator(FlatRight));

	//calculate angles
	FwdDot = FVector::DotProduct(R22Heli_Pawn->GetActorUpVector(), FlatFwd.Vector());
	RightDot = FVector::DotProduct(R22Heli_Pawn->GetActorUpVector(), FlatRight.Vector());
*/

	//calculate the flat forward
	FlatFwd = R22Heli_Pawn->GetSCGraphics()->GetForwardVector().Rotation();
	FlatFwd.Pitch = 0.0f;
	R22Heli_Pawn->ForwardArrow->SetWorldRotation(FRotator(FlatFwd));		

	//calculate flat right
	FlatRight = R22Heli_Pawn->GetSCGraphics()->GetRightVector().Rotation();
	FlatRight.Pitch = 0.0f;
	R22Heli_Pawn->RightArrow->SetWorldRotation(FRotator(FlatRight));

	
	//calculate angles
	FwdDot = FVector::DotProduct(R22Heli_Pawn->GetActorUpVector(), FlatFwd.Vector());
	RightDot = FVector::DotProduct(R22Heli_Pawn->GetActorUpVector(), FlatRight.Vector());
	

}

void UHeliCharacteristics::AutoLevel()
{
	float RightForce = -FwdDot * AutoLevelForce;
	float ForwardForce = RightDot * AutoLevelForce;
	
/*	// Comment
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector) * ForwardForce ),
	true, true);
	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector) * RightForce ),
	true, true);
	
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector) * ForwardForce ),
	   NAME_None, true);
	
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector) * RightForce ),
	          NAME_None, true);
*/
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
	GetRelativeTransform().TransformVector((FVector::ForwardVector) * ForwardForce )
	,NAME_None,true);

	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
	GetRelativeTransform().TransformVector((FVector::RightVector) * RightForce )
	,NAME_None,true);

}


// Called every frame
void UHeliCharacteristics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

