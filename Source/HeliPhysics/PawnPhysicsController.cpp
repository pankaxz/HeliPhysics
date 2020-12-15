// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnPhysicsController.h"
#include "R22Heli_Pawn.h"

UPawnPhysicsController::UPawnPhysicsController()
{

	PrimaryComponentTick.bCanEverTick = true;

	
}


void UPawnPhysicsController::BeginPlay()
{
	Super::BeginPlay();

	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
	// if(R22HeliPawn)
	// {
	// 	R22HeliPawn->GetHeliRootBody()->GetBodyInstance()->SetMassOverride(HeliWeight, true);
	// }
	//
}

void UPawnPhysicsController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(R22HeliPawn)
	{
		
		//R22HeliPawn->GetHeliRootBody()->SetCenterOfMass(HeliCenterOfMass);
		
		//body instance
		// R22HeliPawn->GetHeliRootBody()->GetBodyInstance()->COMNudge = FVector(HeliCenterOfMass);

		// meshComp->SetCenterOfMass(meshComp->GetBodyInstance()->GetCOMPosition() - meshComp->GetBodyInstance()->GetCOMPosition());
		// meshComp->GetBodyInstance()->COMNudge = GetActorLocation() - meshComp->GetBodyInstance()->GetCOMPosition();
		// meshComp->GetBodyInstance()->UpdateMassProperties();

		//
		// R22HeliPawn->GetHeliRootBody()->GetBodyInstance()->COMNudge = FVector(HeliCenterOfMass);
		// R22HeliPawn->GetHeliRootBody()->GetBodyInstance()->UpdateMassProperties();
		//
		// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
		//    FString::Printf(TEXT("HeliCenterOfMass : %s"),
		//    	(*R22HeliPawn->GetHeliRootBody()->GetBodyInstance()->GetCOMPosition().ToString() )));

		
		HandlePhysics();
	}
	
}

void UPawnPhysicsController::HandlePhysics()
{
	
}
