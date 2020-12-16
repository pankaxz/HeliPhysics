// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HeliRotorInterface.h"
#include "Components/ActorComponent.h"
#include "HeliMainRotor.generated.h"

class AR22Heli_Pawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliMainRotor : public UActorComponent, public IHeliRotorInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeliMainRotor();
	
	UPROPERTY()
	AR22Heli_Pawn* R22HeliPawn;

	float GetMainRotorMaxPitch();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Main Rotor")
	float MainRotationSpeedModifier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Main Rotor")
	float MaxPitch = 35.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Main Rotor")
	float CurrentRPMs = 35.0f;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Interface method
	UFUNCTION()
    virtual void UpdateRotor(float DPS) override;

	UFUNCTION()
	float GetCurrentRPMs();

};

