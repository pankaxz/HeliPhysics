// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliController.h"

#include "R22Heli_Pawn.h"

UHeliController::UHeliController()
{
    PrimaryComponentTick.bCanEverTick = true;

}
void UHeliController::BeginPlay()
{
    Super::BeginPlay();
    HeliEngine = Cast<UHeliEngine>(GetOwner()->FindComponentByClass<UHeliEngine>());
}

//todo works fine for 1 engine but what happens if we have to add more in future. seems possible in blueprint. Heli engine is not a good name for future 
void UHeliController::HandleEngine()
{
    if(HeliEngine)
    {
        UE_LOG(LogTemp, Warning, TEXT("Engine Is valid"));
        for(int i = 0; i < EngineArray.Num(); i++)
        {
            UE_LOG(LogTemp, Warning, TEXT("Engine Num : %u"), EngineArray.Num());
            EngineArray[i] = HeliEngine->GetClass();
            HeliEngine->UpdateEngine(R22HeliPawn->GetThrottleInput());
        }
    }
}

void UHeliController::HandlePhysics()
{
    Super::HandlePhysics();

    HandleEngine();
}

void UHeliController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

