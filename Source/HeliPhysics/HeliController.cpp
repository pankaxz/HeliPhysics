
#include "HeliController.h"
#include "HeliEngine.h"
#include "HeliRotorController.h"
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
    HandleCharacteristics();
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
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("%f"), FinalPower));
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

void UHeliController::HandleCharacteristics()
{
}




