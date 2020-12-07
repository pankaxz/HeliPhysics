// Fill out your copyright notice in the Description page of Project Settings.


#include "HeliRotorController.h"
#include "HeliRotorInterface.h"
#include "R22Heli_Pawn.h"


UHeliRotorController::UHeliRotorController()
{

	PrimaryComponentTick.bCanEverTick = true;
	 R22HeliPawn = Cast<AR22Heli_Pawn> (GetOwner());
}

void UHeliRotorController::BeginPlay()
{
	Super::BeginPlay();

	//todo : get all classes that implement interface
	
	// for(UActorComponent* Component : R22HeliPawn->HeliActorComponents)
	// {
	// 	
	// 	if(Component)
	// 	{
	// 		if(Component->GetClass()->ImplementsInterface(UHeliRotorInterface::StaticClass()))
	// 		{
	// 			RotorsList.Add(Component);
	// 		}
	// 	}
 //    }

	// for(auto Component : R22HeliPawn->HeliActorComponents)
	// {
	// 	if(UActorComponent* ComponentCast = Cast<UActorComponent>(Component))
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("PASS")));
	// 	}
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Fail")));
	// }
}



void UHeliRotorController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHeliRotorController::UpdateRotors(float CurrentRPM)
{
	UE_LOG(LogTemp, Warning, TEXT("Current RPM : %f"),CurrentRPM);
}
