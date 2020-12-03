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

void UHeliController::HandleEngine()
{
    if(HeliEngine)
    {
        UE_LOG(LogTemp, Warning, TEXT("Engine Is valid"));
        for(int i = 0; i < EngineArray.Num(); i++)
        {
            //EngineArray[i] = HeliEngine->GetClass();
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

