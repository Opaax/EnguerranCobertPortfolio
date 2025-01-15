// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "TSSpawnSettings.generated.h"

/**
 *  @class UTSSpawnSettings
 *
 *  This class represents the Tanky Spawn Settings for the game.
 *  It is a subclass of UDeveloperSettings and contains various settings related to spawning assets in the game.
 */
UCLASS(config=Game, DefaultConfig, DisplayName = "Tanky Spawn Settings")
class TANKYSURVIVOR_API UTSSpawnSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	/*-------------------------- MEMBERS----------------------------*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, config, Category = Tanky, meta=(AllowedTypes="TSSpawnDefinition"))
	FPrimaryAssetId SpawnDefinition; //In the future this will be some kind of Array or DT of spawn defs.
	
	/*-------------------------- FUNCTION----------------------------*/
public:
	UTSSpawnSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE FPrimaryAssetId GetSpawnDefinition() const {return SpawnDefinition;}
	/*-------------------------- OVERRIDE----------------------------*/
public:
	//~ Begin UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	//~ End UDeveloperSettings interface
};
