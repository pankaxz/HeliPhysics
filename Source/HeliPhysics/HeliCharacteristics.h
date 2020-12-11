// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeliCharacteristics.generated.h"

class AR22Heli_Pawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliCharacteristics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeliCharacteristics();

	UFUNCTION()
	virtual void UpdateCharacteristics(AR22Heli_Pawn* R22Heli_Pawn);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
    virtual void HandleLift(AR22Heli_Pawn* R22Heli_Pawn);

	UFUNCTION()
    virtual void HandleCyclic(AR22Heli_Pawn* R22Heli_Pawn);

	UFUNCTION()
    virtual void HandlePedals(AR22Heli_Pawn* R22Heli_Pawn);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
