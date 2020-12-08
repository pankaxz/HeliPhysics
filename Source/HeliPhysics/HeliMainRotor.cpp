// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliMainRotor.h"
#include "R22Heli_Pawn.h"
#include "HeliRotorInterface.h"


UHeliMainRotor::UHeliMainRotor()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
}


void UHeliMainRotor::BeginPlay()
{
	Super::BeginPlay();

	
}


void UHeliMainRotor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//todo  alert : Something wrong here
void UHeliMainRotor::UpdateRotor(float DPS)
{
	float LocalDPS = DPS * GetWorld()->GetDeltaSeconds() * 0.5f;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("DPS %f"), LocalDPS));
	//R22HeliPawn->SC_MainMastRotor->SetWorldRotation((FRotator(0,0,LocalDPS)), false, 0, ETeleportType::None);
	//transform.Rotate(Vector3.up, DPS * Time.deltaTime * 0.5f);
	
}

