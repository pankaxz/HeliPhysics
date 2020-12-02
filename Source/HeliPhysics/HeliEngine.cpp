// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliEngine.h"

// Sets default values for this component's properties
UHeliEngine::UHeliEngine()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UHeliEngine::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHeliEngine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHeliEngine::UpdateEngine(float ThrottleInput)
{
	
}


void UHeliEngine::SetCurrentHP()
{
}

void UHeliEngine::SetCurrentRPM()
{
}

float UHeliEngine::GetCurrentHP()
{
	return CurrentHP;
}

float UHeliEngine::GetCurrentRPM()
{
	return CurrentRPM;
}

