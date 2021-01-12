
#include "HeliController.h"
#include "HeliEngine.h"
#include "HeliRotorController.h"
#include "HeliCharacteristics.h"
#include "R22Heli_Pawn.h"

UHeliController::UHeliController()
{
    PrimaryComponentTick.bCanEverTick = true;

}

void UHeliController::BeginPlay()
{
    Super::BeginPlay();
    
    HeliEngine = GetOwner()->FindComponentByClass<UHeliEngine>();
    HeliRotorController = GetOwner()->FindComponentByClass<UHeliRotorController>();
    HeliCharacteristics = GetOwner()->FindComponentByClass<UHeliCharacteristics>();
   
    EngineArray.Add(HeliEngine);
}

void UHeliController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UHeliController::HandlePhysics()
{
    Super::HandlePhysics();

    HandleEngine();
    HandleRotors();
    HandleCharacteristics(R22HeliPawn);
}


//note: works fine for 1 engine. To Create more engine, add tags and check "(Engine->ComponentHasTag("EngineTwo"))"
void UHeliController::HandleEngine()
{
    if(HeliEngine)
    {
        // GetOwner()->GetComponents(HeliEngineComponents);
        for (UHeliEngine* Engine : EngineArray)
        {
            HeliEngine = Engine;
            HeliEngine->UpdateEngine(R22HeliPawn->GetStickyThrottleInput());
            float FinalPower = HeliEngine->GetCurrentHP();
        }
    }
}

void UHeliController::HandleRotors()
{
    if(HeliRotorController && EngineArray.Num()>0)
    {
        HeliRotorController->UpdateRotors(HeliEngine->GetCurrentRPM());
    }
}

void UHeliController::HandleCharacteristics(AR22Heli_Pawn* R22Heli_Pawn)
{
    if(HeliCharacteristics)
    {
        HeliCharacteristics->UpdateCharacteristics();
    }
    
}



