// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnPhysicsController.h"
#include "HeliController.generated.h"

/**
 * 
 */
UCLASS()
class HELIPHYSICS_API UHeliController : public UPawnPhysicsController
{
	GENERATED_BODY()
	UHeliController();

protected:
	
	virtual void HandlePhysics() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
