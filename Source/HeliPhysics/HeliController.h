
#pragma once

#include "CoreMinimal.h"
#include "PawnPhysicsController.h"
#include "HeliController.generated.h"

/**
 * 
 */

class UHeliEngine;
class UHeliRotorController;
class UHeliCharacteristics;

UCLASS()
class HELIPHYSICS_API UHeliController : public UPawnPhysicsController
{
	GENERATED_BODY()
	UHeliController();

	
	
protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleEngine();

	UFUNCTION(BlueprintCallable)
	virtual void HandleRotors();
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleCharacteristics(AR22Heli_Pawn* R22Heli_Pawn);
	
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HandlePhysics() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Heli Controller")
	TArray<UHeliEngine*> EngineArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Heli Controller")
	UHeliEngine* HeliEngine;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Heli Controller")
	UHeliRotorController* HeliRotorController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Heli Controller")
	UHeliCharacteristics*  HeliCharacteristics;


	
};
