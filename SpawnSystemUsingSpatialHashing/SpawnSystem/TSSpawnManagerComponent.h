// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TSSpawnManagerComponent.generated.h"


class UTSSpawnDefinition;

UCLASS(ClassGroup=(TankySurvivor), meta=(BlueprintSpawnableComponent))
class TANKYSURVIVOR_API UTSSpawnManagerComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	/*-------------------------- MEMBERS----------------------------*/
private:
	UPROPERTY(VisibleInstanceOnly, Category= "Runtime")
	UTSSpawnDefinition* SpawnDefinition;
	
	/*-------------------------- FUNCTION----------------------------*/
	UFUNCTION()
	void SpawnTest(float MinDist, float MaxDist, UClass* SpawnClass) const;
	
	/*-------------------------- OVERRIDE----------------------------*/
protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
};
