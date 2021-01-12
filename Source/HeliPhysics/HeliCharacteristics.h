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
	virtual void UpdateCharacteristics();
	
	UPROPERTY()
	AR22Heli_Pawn* R22Heli_Pawn;
	
	//Collective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float MaxLiftForce = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float AscendForce = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float DescentForce = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characteristics - Physics Properties")
	float DownForce = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Characteristics - Physics Properties")
	float IdleForce = 0.0f;
	
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
    virtual void HandleLift();

	UFUNCTION()
    virtual void HandleCyclic();

	UFUNCTION()
    virtual void HandlePedals();

	UPROPERTY()
	UHeliMainRotor* HeliMainRotor;

	UFUNCTION()
    void CalculateAngle();

	UFUNCTION()
    void AutoLevel();

	UPROPERTY()
	FRotator FlatFwd;

	UPROPERTY()
	FRotator FlatRight;

	UPROPERTY()
	float FwdDot;

	UPROPERTY()
	float RightDot;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
