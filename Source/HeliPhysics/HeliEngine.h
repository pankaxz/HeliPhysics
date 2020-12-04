// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "HeliEngine.generated.h"

class UCurveFloat;
class AR22Heli_Pawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class HELIPHYSICS_API UHeliEngine : public UActorComponent

{
	GENERATED_BODY()

	float CurrentHP;
	float CurrentRPM;

	float FinalHP;
	float FinalRPM;
	
public:

	UHeliEngine();

	//todo change it to void 
	UFUNCTION(BlueprintCallable)
	void UpdateEngine(float ThrottleInput);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float MaxHP = 140.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float MaxRPM = 2700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float PowerDelay = 2.0f;

	//Getter Functions
	float GetCurrentHP() const;
	float GetCurrentRPM() const;

	UFUNCTION()
	void PowerDelayProgress(float Value);
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	AR22Heli_Pawn* R22HeliPawn;

	//Setter Functions
	void SetCurrentHP();
	void SetCurrentRPM();

	FTimeline PowerCurve;
	UPROPERTY(EditAnywhere, Category="Power Delay Timeline")
	UCurveFloat* CurveFloat;

	//todo: Add timeline parameters
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
