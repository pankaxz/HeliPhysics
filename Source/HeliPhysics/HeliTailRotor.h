// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HeliRotorInterface.h"
#include "Components/ActorComponent.h"
#include "HeliTailRotor.generated.h"


class AR22Heli_Pawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliTailRotor : public UActorComponent, public IHeliRotorInterface
{
	GENERATED_BODY()

public:	
	UHeliTailRotor();
	
	float GetTailRotorMaxPitch();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AR22Heli_Pawn* R22HeliPawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Tail Rotor")
	float TailRotationSpeedModifier = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Main Rotor")
	float MaxPitch = 45.0f;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Interface method
	UFUNCTION()
    virtual void UpdateRotor(float DPS) override;
		
};
