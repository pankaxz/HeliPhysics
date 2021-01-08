// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliCharacteristics.h"

#include "GenericPlatform/GenericPlatformMath.h"
#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

UHeliCharacteristics::UHeliCharacteristics()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliCharacteristics::UpdateCharacteristics(AR22Heli_Pawn* R22Heli_Pawn)
{
	HandleLift(R22Heli_Pawn);
	HandlePedals(R22Heli_Pawn);
	HandleCyclic(R22Heli_Pawn);
	// CalculateAngle(R22Heli_Pawn);
	// AutoLevel(R22Heli_Pawn);

	PawnQuat = R22Heli_Pawn->GetActorQuat();
}


void UHeliCharacteristics::BeginPlay()
{
	Super::BeginPlay();

	HeliMainRotor = GetOwner()->FindComponentByClass<UHeliMainRotor>();
	
}


void UHeliCharacteristics::HandleLift(AR22Heli_Pawn* R22Heli_Pawn)
{
	{
		// R22Heli_Pawn->GetHeliRootBody()->AddForce(LiftForce * (FMath::Pow(NormalizedRPMs,2.0f))
		//                                            * FMath::Pow(R22Heli_Pawn->GetStickyCollectiveInput(), 2.0f), NAME_None, false);
	}

	float NormalizedRPMs = HeliMainRotor->GetCurrentRPMs()/500.0f;
	
	FVector LiftForce;
	
	//Todo : Forces acting fine. Looks acceptable. Ascends Force need to act more fast.
	if(R22Heli_Pawn->GetRawCollectiveInput() > 0)
	{
		LiftForce = R22Heli_Pawn->GetActorUpVector() * R22Heli_Pawn->GetRawCollectiveInput()  * AscendForce;
	}
	//TODO : Idle needs to activate fast, maybe interp faster. 
	if(R22Heli_Pawn->GetRawCollectiveInput() == 0)
	{
		LiftForce = R22Heli_Pawn->GetActorUpVector() * IdleForce ;
	}
	//TODO : Descent Force has to stop if landed
	if(R22Heli_Pawn->GetRawCollectiveInput() < 0)
	{
		LiftForce = - R22Heli_Pawn->GetActorUpVector() * R22Heli_Pawn->GetRawCollectiveInput()  * DescentForce;
	}

	//Todo : Angular Daming set tp 0.7 !! 
	//
	R22Heli_Pawn->GetHeliRootBody()->AddForce( LiftForce * NormalizedRPMs, NAME_None, false);


	
	/*if(R22Heli_Pawn->GetRawCollectiveInput() > 0) 
	{
		/*Ascend
		 *Should apply force in upward direction
		 #1#
		
		FVector LiftForce = R22Heli_Pawn->GetActorUpVector() *  AscendForce;
		
		R22Heli_Pawn->GetHeliRootBody()->AddForce( LiftForce * NormalizedRPMs * R22Heli_Pawn->GetStickyCollectiveInput(), NAME_None, false);
		// R22Heli_Pawn->GetHeliRootBody()->AddForce( LiftForce, NAME_None, false);

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
                            FString::Printf(TEXT("Ascending")));

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
                            FString::Printf(TEXT("LiftForce : %s"), *LiftForce.ToString()));

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
                            FString::Printf(TEXT("Actual LiftForce applied : %s"), *(LiftForce * NormalizedRPMs * R22Heli_Pawn->GetStickyCollectiveInput()).ToString()));

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
                    FString::Printf(TEXT("Gravity LiftForce : %f"), FMath::Abs(GetWorld()->GetGravityZ()) * (R22Heli_Pawn->GetHeliRootBody()->GetMass())));

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
                    FString::Printf(TEXT("Mass : %f"),R22Heli_Pawn->GetHeliRootBody()->GetMass()));

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
                    FString::Printf(TEXT("Velocity : %f"),(R22Heli_Pawn->GetHeliRootBody()->GetPhysicsLinearVelocity().Size())));

	}
	
	float Accel = R22Heli_Pawn->GetHeliRootBody()->GetPhysicsLinearVelocity().Size()/GetWorld()->GetDeltaSeconds();

	if(R22Heli_Pawn->GetRawCollectiveInput() == 0) 
	{
		/*Idle
		*
		#1#
		FVector DownwardForce = R22Heli_Pawn->GetActorUpVector() *
				FMath::FInterpTo((R22Heli_Pawn->GetHeliRootBody()->GetMass() * Accel),
					IdleForce, GetWorld()->GetDeltaSeconds(),
					(IdleForce / R22Heli_Pawn->GetHeliRootBody()->GetMass() * Accel) * 100000 );
		
		R22Heli_Pawn->GetHeliRootBody()->AddForce(DownwardForce * NormalizedRPMs , NAME_None, false);
		// R22Heli_Pawn->GetHeliRootBody()->AddForce( LiftForce, NAME_None, false);


		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
        FString::Printf(TEXT("IDLE Force : %f "), DownwardForce.Z));
		
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
		FString::Printf(TEXT("InterpSpeed : %f "), ((IdleForce / R22Heli_Pawn->GetHeliRootBody()->GetMass() * Accel))));
		

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
        FString::Printf(TEXT("Acting Force : %f "),R22Heli_Pawn->GetHeliRootBody()->GetMass() * Accel));
	}*/

	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,FString::Printf(TEXT("--------------------------------------------")));

	
}


//TODO: Later

///--------------------------------------------------
	//Cyclic force is bad
void UHeliCharacteristics::HandleCyclic(AR22Heli_Pawn* R22Heli_Pawn)
{

	float CyclicXForce = R22Heli_Pawn->GetCyclicInput().X * CyclicForce;
	float CyclicYForce = R22Heli_Pawn->GetCyclicInput().Y * CyclicForce;

	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector)* CyclicXForce),
		true, true);
	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector)* CyclicYForce),
		true, true);

	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector)* CyclicXForce),
	NAME_None, true);

	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector)* CyclicYForce),
	NAME_None, true);
	
	
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
	GetRelativeTransform().TransformVector((FVector::ForwardVector) * CyclicXForce )
	,NAME_None,true);

	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
	GetRelativeTransform().TransformVector((FVector::RightVector) * CyclicYForce )
	,NAME_None,true);

	FVector ForwardVec = FlatFwd.Vector() * FwdDot;
	FVector RightVec = FlatRight.Vector() * RightDot;
	
	FVector FinalCylicDirection = ForwardVec + RightVec * (CyclicForce * CyclicForceMultiplier);
	R22Heli_Pawn->GetHeliRootBody()->AddForce(FinalCylicDirection, NAME_None, true);

}

void UHeliCharacteristics::HandlePedals(AR22Heli_Pawn* R22Heli_Pawn)
{
	if(R22Heli_Pawn->GetPedalInput())
	{
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians(FVector(0,0,R22Heli_Pawn->GetPedalInput() * TailForce),
	true, true);
		
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(FVector::UpVector * R22Heli_Pawn->GetPedalInput() * TailForce,
	NAME_None, true);
        
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians(R22Heli_Pawn->GetHeliRootBody()->
	GetRelativeTransform().TransformVector((FVector::UpVector.ZAxisVector))* R22Heli_Pawn->GetPedalInput() * TailForce
	,NAME_None,true);
	}

}

//todo:: Debug line not working
void UHeliCharacteristics::CalculateAngle(AR22Heli_Pawn* R22Heli_Pawn)
{	
	//old---
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

void UHeliCharacteristics::AutoLevel(AR22Heli_Pawn* R22Heli_Pawn)
{
	float RightForce = -FwdDot * AutoLevelForce;
	float ForwardForce = RightDot * AutoLevelForce;
	
	// Comment
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector) * ForwardForce ),
	true, true);
	
	R22Heli_Pawn->GetPhysicsFBodyInstance()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector) * RightForce ),
	true, true);
	
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::ForwardVector) * ForwardForce ),
	   NAME_None, true);
	
	R22Heli_Pawn->GetHeliRootBody()->AddTorqueInRadians((PawnQuat.RotateVector(FVector::RightVector) * RightForce ),
	          NAME_None, true);

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

