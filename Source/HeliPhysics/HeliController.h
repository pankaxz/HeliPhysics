
#pragma once

#include "CoreMinimal.h"
#include "PawnPhysicsController.h"
#include "HeliController.generated.h"

/**
 * 
 */

class UHeliEngine;
class UHeliRotorController;

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
	virtual void HandleCharacteristics();

	
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HandlePhysics() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	TArray<UHeliEngine*> EngineArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	UHeliEngine* HeliEngine;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pawn Physics Controller")
	UHeliRotorController* HeliRotorController;
	
};
