// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnPhysicsController.h"
#include "R22Heli_Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPawnPhysicsController::UPawnPhysicsController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UPawnPhysicsController::BeginPlay()
{
	Super::BeginPlay();

	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
	HeliCenterOfMass = R22HeliPawn->GetHeliCenterOfMass();
	
	if(R22HeliPawn)
	{
		R22HeliPawn->GetHeliRootBody()->SetMassOverrideInKg(NAME_None, HeliWeight, true);
		//R22HeliPawn->GetHeliRootBody()->SetCenterOfMass(HeliCenterOfMass, NAME_None);
	}
}

// Called every frame
void UPawnPhysicsController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(R22HeliPawn)
	{
		
		HandlePhysics();
	}

}

void UPawnPhysicsController::HandlePhysics()
{
	UE_LOG(LogTemp, Warning, TEXT("Handleing physics"));
}