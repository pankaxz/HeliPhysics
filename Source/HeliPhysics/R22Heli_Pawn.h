// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "R22Heli_Pawn.generated.h"


//classes
class UCapsuleComponent;
class UInputController;
class UPawnPhysicsController;
class UHeliEngine;
class UHeliController;
class UHeliRotorController;
class UHeliMainRotor;
class UHeliTailRotor;

UCLASS()
class HELIPHYSICS_API AR22Heli_Pawn : public APawn
{
	GENERATED_BODY()

public:
	
	AR22Heli_Pawn();

	//Getters
	float GetHorizontalInput() const;
	float GetVerticalInput() const;
	
	float GetRawThrottleInput() const;
	float GetStickyThrottleInput() const;
	
	float GetPedalInput() const;
	float GetCollectiveInput() const;
	
	FVector2D GetCyclicInput() const;
	UStaticMeshComponent* GetHeliRootBody() const;
	FVector GetHeliCenterOfMass() const;

	//Rotors 
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SC_MainMastRotor;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SC_TailMastRotor;
	

protected:
	virtual void BeginPlay() override;
	
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="HeliPawn",  meta = (AllowProtectedAccess = "true"))
    UStaticMeshComponent* SM_RootBody;
    
    UPROPERTY(EditDefaultsOnly)
    USceneComponent* SC_Graphics;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SC_Body;
	
    UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* Col_Mast;
    
    UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* Col_RSkid;
    
    UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* Col_LSkid;
    
    UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* Col_Tail;
    
    UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* Col_Fuselage;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SC_HeliCenterOfMass;

	//Actor Components
	//
	//

	
	//Pawn controller
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnPhysicsController* PawnPhysicsControllerVar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeliController* HeliController;
	
	//Engine
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeliEngine* HeliEngineNew;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeliRotorController*  HeliRotorController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeliMainRotor*  HeliMainRotor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeliTailRotor*  HeliTailRotor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UActorComponent*> HeliActorComponents;

	
private:
	//Setters

	void SetHorizontalInput(float AxisValue);
	void SetVerticalInput(float AxisValue);
	void SetRawThrottleInput(float AxisValue);
	void SetStickyThrottleInput();
	void SetPedalInput(float AxisValue);
	void SetCollectiveInput(float AxisValue);
	void SetCyclicInput();
	
	//Input Variables
	//
	//Horizontal Input - w s
	float HorizontalInput = 0.0f;
	
	//Vertical Input - a d
	float VerticalInput = 0.0f;
	
	//Raw Throttle Input + -
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float ThrottleInput = 0.0f;

	//Sticky Throttle Input 
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float StickyThrottle = 0.0f;

	//Pedal Input - right left
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float PedalInput = 0.0f;
	
	//Collective Input - up down
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float CollectiveInput = 0.0f;
	
	// Cyclic input - X = Horizontal Input			
	// Cyclic input - Y = Vertical Input			
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	FVector2D CyclicInput = FVector2D().ZeroVector;

};
