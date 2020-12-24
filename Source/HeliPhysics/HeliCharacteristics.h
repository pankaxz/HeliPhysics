// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeliCharacteristics.generated.h"

class AR22Heli_Pawn;
class UHeliMainRotor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliCharacteristics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeliCharacteristics();

	UFUNCTION()
	virtual void UpdateCharacteristics(AR22Heli_Pawn* R22Heli_Pawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float MaxLiftForce = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float TailForce = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float CyclicForce = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float CyclicForceMultiplier = 1000.0f;

	FQuat PawnQuat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float AutoLevelForce = -2;

	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
    virtual void HandleLift(AR22Heli_Pawn* R22Heli_Pawn);

	UFUNCTION()
    virtual void HandleCyclic(AR22Heli_Pawn* R22Heli_Pawn);

	UFUNCTION()
    virtual void HandlePedals(AR22Heli_Pawn* R22Heli_Pawn);

	UPROPERTY()
	UHeliMainRotor* HeliMainRotor;

	UFUNCTION()
    void CalculateAngle(AR22Heli_Pawn* R22Heli_Pawn);

	UFUNCTION()
    void AutoLevel(AR22Heli_Pawn* R22Heli_Pawn);

	UPROPERTY()
	FRotator FlatFwd;

	UPROPERTY()
	FRotator FlatRight;

	UPROPERTY()
	float FwdDot;

	UPROPERTY()
	float RightDot;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
};
