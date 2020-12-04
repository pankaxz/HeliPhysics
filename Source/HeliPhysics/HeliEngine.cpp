

#include "HeliEngine.h"
#include "R22Heli_Pawn.h"

UHeliEngine::UHeliEngine()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UHeliEngine::BeginPlay()
{
	Super::BeginPlay();
	R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
	
}

void UHeliEngine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHeliEngine::UpdateEngine(float ThrottleInput)
{
	UE_LOG(LogTemp, Warning, TEXT("Throttle input : %f"),ThrottleInput);
	//Calculate HorsePower
	float WantedHP = ThrottleInput* MaxHP;
	CurrentHP = FMath::Lerp(CurrentHP,WantedHP,GetWorld()->GetDeltaSeconds() * PowerDelay);

	//Calculate RPM
	float WantedRPM = ThrottleInput * MaxRPM ;
	CurrentRPM = FMath::Lerp(CurrentRPM,WantedRPM,GetWorld()->GetDeltaSeconds() * PowerDelay);
}


void UHeliEngine::SetCurrentHP()
{
}

void UHeliEngine::SetCurrentRPM()
{
}

float UHeliEngine::GetCurrentHP() const
{
	return CurrentHP;
}

float UHeliEngine::GetCurrentRPM() const
{
	return CurrentRPM;
}

void UHeliEngine::PowerDelayProgress(float Value)
{
}

