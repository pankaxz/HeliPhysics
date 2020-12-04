
#include "HeliController.h"
#include "R22Heli_Pawn.h"

UHeliController::UHeliController()
{
    PrimaryComponentTick.bCanEverTick = true;

}
void UHeliController::BeginPlay()
{
    Super::BeginPlay();
    
    HeliEngine = GetOwner()->FindComponentByClass<UHeliEngine>();
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
    HandleCharacteristics();
}


//todo: works fine for 1 engine. To Create more engine, add tags and check "(Engine->ComponentHasTag("EngineTwo"))"
void UHeliController::HandleEngine()
{
    if(HeliEngine)
    {
        GetOwner()->GetComponents(HeliEngineComponents);
        for (UHeliEngine* Engine : EngineArray)
        {
            HeliEngine = Engine;
            HeliEngine->UpdateEngine(R22HeliPawn->GetThrottleInput());
            float FinalPower = HeliEngine->GetCurrentHP();
            UE_LOG(LogTemp, Warning, TEXT("Final Power : %f"),FinalPower);
        }
    }
}

void UHeliController::HandleCharacteristics()
{
}




