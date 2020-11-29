// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UPawnController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnController();

	//variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn Controller")
	float MaxSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn Controller")
	FVector MovemmentDirection = FVector(0.0f,0.0f,0.0f);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void HandlePhysics();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};