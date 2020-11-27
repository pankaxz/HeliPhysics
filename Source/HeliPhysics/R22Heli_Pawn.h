// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "R22Heli_Pawn.generated.h"

class UCapsuleComponent;
UCLASS()
class HELIPHYSICS_API AR22Heli_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AR22Heli_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    UStaticMeshComponent* SM_PhysicsBox;
    
    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    USceneComponent* SC_Graphics;
    
    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    UCapsuleComponent* COL_Mast;
    
    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    UCapsuleComponent* COL_RSkid;
    
    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    UCapsuleComponent* COL_LSkid;
    
    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    UCapsuleComponent* COL_Tail;

    UPROPERTY(VisibleAnywhere, Category="HeliPawn")
    UCapsuleComponent* COL_Fuselage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
