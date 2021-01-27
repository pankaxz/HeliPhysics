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
class UHeliCharacteristics;
class UArrowComponent;

		// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
		// 	FString::Printf(TEXT("DPS At Main Rotor %f"), LocalDPS));
		
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
	
	float GetRawCollectiveInput() const;
	float GetStickyCollectiveInput() const;
	
	float GetLookRightInput() const;
	float GetLookUpInput() const;
	
	FVector2D GetCyclicInput() const;
	UStaticMeshComponent* GetHeliRootBody() const;
	USceneComponent* const GetSCGraphics() const;
	FBodyInstance* GetPhysicsFBodyInstance();

	//Rotors 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SC_MainMastRotor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SC_TailMastRotor;

	UPROPERTY()
	UStaticMeshComponent* SM_RMainBlade;

	UPROPERTY()
	UStaticMeshComponent* SM_LMainBlade;

	UPROPERTY()
	UStaticMeshComponent* SM_RTailBlade;
	
	UPROPERTY()
	UStaticMeshComponent* SM_LTailBlade;

	UPROPERTY()
	UArrowComponent* ForwardArrow; 

	UPROPERTY()
	UArrowComponent* RightArrow;
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

	/*
	 *The center of mass is being set by a dummy collider with custom collisions. It work well with the way I want to move the COM.
	 *Physics FBodyHandler is the body isntance for it.
	 */
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* HeliPhysicsHandler;

	FBodyInstance* PhysicsFBodyHandler;
	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeliCharacteristics*  HeliCharacteristics;


public:
	
	virtual void Tick(float DeltaTime) override;

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
	
	void SetRawCollectiveInput(float AxisValue);
	void SetStickyCollectiveInput();
	
	void SetCyclicInput();

	void SetLookRightInput(float AxisValue);
	void SetLookUpInput(float AxisValue);
	
	//Input Variables
	//
	//
	//Camera
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float LookRightInput = 0.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float LookUpInput = 0.0f;
	
	//Horizontal Input - w s
	float HorizontalInput = 0.0f;
	
	//Vertical Input - a d
	float VerticalInput = 0.0f;
	
	//Raw Throttle Input + -
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float ThrottleInput = 0.0f;

	//Sticky Throttle Input 
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float StickyThrottleInput = 0.0f;

	//Pedal Input - right left
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float PedalInput = 0.0f;
	
	//Collective Input - up down
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float CollectiveInput = 0.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float StickyCollectiveInput = 0.0f;
	
	
	// Cyclic input - X = Horizontal Input			
	// Cyclic input - Y = Vertical Input			
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	FVector2D CyclicInput = FVector2D().ZeroVector;

};
