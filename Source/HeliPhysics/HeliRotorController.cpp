// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliRotorController.h"


UHeliRotorController::UHeliRotorController()
{

	PrimaryComponentTick.bCanEverTick = true;
}


void UHeliRotorController::UpdateRotors(float CurrentRPM)
{
	UE_LOG(LogTemp, Warning, TEXT("Current RPM : %f"),CurrentRPM);
}


void UHeliRotorController::BeginPlay()
{
	Super::BeginPlay();


	
}



void UHeliRotorController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

