// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeliEngine.generated.h"

class UCurveFloat;
class AR22Heli_Pawn;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class HELIPHYSICS_API UHeliEngine : public UActorComponent

{
	GENERATED_BODY()
	
	/**
	*Engine variables
	*/
	float CurrentHP;
	float CurrentRPM;
	float FinalHP;
	float FinalRPM;

	
public:

	UHeliEngine();

	UFUNCTION(BlueprintCallable)
	void UpdateEngine(float ThrottleInput);
	
	/**
	*Engine variables
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float MaxHP = 140.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float MaxRPM = 2700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float PowerDelay = 2.0f;

	/**
	*Getter Functions
	*/
	float GetCurrentHP() const;
	float GetCurrentRPM() const;

	/**
	*Curve 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Power curve")
	UCurveFloat* FPowerCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Power curve")
	float CurrentHPNonCurve;
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY()
	AR22Heli_Pawn* R22HeliPawn;

	/**
	*Setter Function
	*/
	void SetCurrentHP();
	void SetCurrentRPM();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
 
};
