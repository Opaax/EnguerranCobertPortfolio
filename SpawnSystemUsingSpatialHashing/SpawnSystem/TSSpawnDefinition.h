// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TSSpawnDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Const)
class TANKYSURVIVOR_API UTSSpawnDefinition : public UPrimaryDataAsset
{
	GENERATED_UCLASS_BODY()

	/*-------------------------- MEMBERS----------------------------*/
protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> Spawnable;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MinDistanceSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MaxDistanceSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnRate;
	
/*-------------------------- FUNCTION----------------------------*/
public:
	FORCEINLINE UClass* GetSpawnable() const { return Spawnable;}
	FORCEINLINE float GetMinDistance() const { return MinDistanceSpawn;}
	FORCEINLINE float GetMaxDistance() const { return MaxDistanceSpawn;}
	FORCEINLINE float GetSpawnRate() const { return SpawnRate;}
/*-------------------------- OVERRIDE----------------------------*/

};
