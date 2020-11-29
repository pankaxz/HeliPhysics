// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputController.generated.h"

// UENUM(BlueprintType)
// enum EInputType
// {
// 	Keyboard 	UMETA(DisplayName = "Keyboard"),
// 	Xbox 		UMETA(DisplayName = "XBOX Controller")
// };

class AR22Heli_Pawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UInputController : public UActorComponent
{
	GENERATED_BODY()
	
	//
	// UFUNCTION(BlueprintCallable)
 //    void FSetInputType(EInputType InputDeviceType);
	
public:	
	// Sets default values for this component's properties
	UInputController();


	UPROPERTY(BlueprintReadOnly)
	bool bUseKeyboardInput;

	UPROPERTY(BlueprintReadOnly)
	bool bUseXboxInput;
	
	USceneComponent* UpdatedComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AR22Heli_Pawn* R22HeliPawn;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputType")
	// TEnumAsByte<EInputType> InputType;
};

