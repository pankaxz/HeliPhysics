// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnPhysicsController.generated.h"

class AR22Heli_Pawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )


class HELIPHYSICS_API UPawnPhysicsController : public UActorComponent
{
	GENERATED_BODY()

public:

	
	UPawnPhysicsController();

	//variables

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn Physics Controller")
	// float MaxSpeed = 1.0f;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn Physics Controller")
	// FVector MovementDirection = FVector(0.0f,0.0f,0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn Physics Controller")
	FVector HeliCenterOfMass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	float HeliWeight = 10.0f;

	
	UFUNCTION()
	virtual void HandlePhysics() ;

	UPROPERTY()
	AR22Heli_Pawn* R22HeliPawn;

	
protected:
	
	virtual void BeginPlay() override;



public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
