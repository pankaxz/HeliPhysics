// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliController.h"

UHeliController::UHeliController()
{
    PrimaryComponentTick.bCanEverTick = true;
	
}

void UHeliController::HandlePhysics()
{
    UE_LOG(LogTemp, Warning, TEXT("Handleing physics in Child"));
}

void UHeliController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    HandlePhysics();
}
