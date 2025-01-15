// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TSSpawnLocationActor.generated.h"

UCLASS()
class TANKYSURVIVOR_API ATSSpawnLocationActor : public AActor
{
	GENERATED_UCLASS_BODY()
	/*-------------------------- MEMBERS----------------------------*/
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Visual;

	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
	/*-------------------------- FUNCTION----------------------------*/
	
	/*-------------------------- OVERRIDE----------------------------*/
	
};
