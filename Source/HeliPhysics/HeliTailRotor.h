// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HeliRotorInterface.h"
#include "Components/ActorComponent.h"
#include "HeliTailRotor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UHeliTailRotor : public UActorComponent, public IHeliRotorInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeliTailRotor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Interface method
	UFUNCTION()
    virtual void UpdateRotor() override;
		
};
