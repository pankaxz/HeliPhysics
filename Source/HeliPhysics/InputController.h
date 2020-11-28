// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputController.generated.h"

UENUM(BlueprintType)
enum EInputType
{
	Keyboard 	UMETA(DisplayName = "Keyboard"),
	Xbox 		UMETA(DisplayName = "XBOX Controller")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELIPHYSICS_API UInputController : public UActorComponent
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
    void FSetInputType(EInputType InputDeviceType);
	
public:	
	// Sets default values for this component's properties
	UInputController();


	UPROPERTY(BlueprintReadOnly)
	bool bUseKeyboardInput;

	UPROPERTY(BlueprintReadOnly)
	bool bUseXboxInput;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputType")
	TEnumAsByte<EInputType> InputType;
};

