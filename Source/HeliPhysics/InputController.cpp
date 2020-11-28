// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"

// Sets default values for this component's properties
UInputController::UInputController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInputController::BeginPlay()
{
	Super::BeginPlay();
}

void UInputController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// =>WARNING : Setting this on tick to check for the change in enum
	FSetInputType(this->InputType);
}

void UInputController::FSetInputType(EInputType InputDeviceType)
{
	if(InputDeviceType == Keyboard)
	{
		bUseKeyboardInput = true;
		bUseXboxInput = false;
	}
	else
	{
		bUseKeyboardInput = false;
		bUseXboxInput = true;
	}
}
