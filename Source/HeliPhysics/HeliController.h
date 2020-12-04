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
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void HandleEngine();

	
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HandlePhysics() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	TArray<TSubclassOf<UHeliEngine>> EngineArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	UHeliEngine* HeliEngine;
	
};
