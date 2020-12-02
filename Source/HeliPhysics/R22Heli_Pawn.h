// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "R22Heli_Pawn.generated.h"

class UCapsuleComponent;
class UInputController;
class UPawnPhysicsController;
UCLASS()
class HELIPHYSICS_API AR22Heli_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AR22Heli_Pawn();

	//Getters
	float GetHorizontalInput();
	float GetVerticalInput() ;
	float GetThrottleInput();
	float GetPedalInput();
	float GetCollectiveInput();
	FVector2D GetCyclicInput();
	UStaticMeshComponent* GetHeliRootBody();
	FVector GetHeliCenterOfMass();
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="HeliPawn",  meta = (AllowProtectedAccess = "true"))
    UStaticMeshComponent* SM_RootBody;
    
    UPROPERTY(EditDefaultsOnly)
    USceneComponent* SC_Graphics;
    
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

	//Pawn controller
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnPhysicsController* PawnPhysicsControllerVar;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Setters

	void SetHorizontalInput(float AxisValue);
	void SetVerticalInput(float AxisValue);
	void SetThrottleInput(float AxisValue);
	void SetPedalInput(float AxisValue);
	void SetCollectiveInput(float AxisValue);
	void SetCyclicInput();
	//Input Variables
	//
	//Horizontal Input - w s
	float HorizontalInput = 0.0f;
	
	//Vertical Input - a d
	float VerticalInput = 0.0f;
	
	//Throttle Input 9 0 
	UPROPERTY(VisibleAnywhere, Category = "InputTest")
	float ThrottleInput = 0.0f;
	
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
