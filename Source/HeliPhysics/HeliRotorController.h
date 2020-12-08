// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HeliRotorInterface.h"
#include "Components/ActorComponent.h"
#include "HeliRotorController.generated.h"

class AR22Heli_Pawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliRotorController : public UActorComponent, public IHeliRotorInterface
{
	GENERATED_BODY()

public:
	
	UHeliRotorController();

	void UpdateRotors(float CurrentRPM);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	TArray<UActorComponent*> RotorsList;
	
	UPROPERTY()
	AR22Heli_Pawn* R22HeliPawn;

	
protected:

	virtual void BeginPlay() override;


	
public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};


