// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeliEngine.generated.h"

class AR22Heli_Pawn; 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliEngine : public UActorComponent
{
	GENERATED_BODY()

	float CurrentHP;
	float CurrentRPM;
	
public:	
	// Sets default values for this component's properties
	UHeliEngine();

	UFUNCTION(BlueprintCallable)
	void UpdateEngine(float ThrottleInput);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float MaxHP = 140.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float MaxRPM = 2700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heli Engine")
	float PowerDelay = 2.0f;


	//Getter Functions
	float GetCurrentHP();
	float GetCurrentRPM();
	
protected:
	
	virtual void BeginPlay() override;
	
	AR22Heli_Pawn* R22HeliPawn;

	//Setter Functions
	void SetCurrentHP();
	void SetCurrentRPM();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
