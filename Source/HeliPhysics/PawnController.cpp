// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnController.h"
#include "R22Heli_Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPawnController::UPawnController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
}


void UPawnController::HandlePhysics()
{
	UE_LOG(LogTemp, Warning, TEXT("Handleing physics"));
}

// Called when the game starts
void UPawnController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UPawnController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(R22HeliPawn)
	{
		HandlePhysics();
	}

}