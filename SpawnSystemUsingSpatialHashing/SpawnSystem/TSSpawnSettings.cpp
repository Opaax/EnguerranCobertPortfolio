// Copyright 2025 Enguerran COBERT. all right reserved.

#include "SpawnSystem/TSSpawnSettings.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TSSpawnSettings)

UTSSpawnSettings::UTSSpawnSettings(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

FName UTSSpawnSettings::GetCategoryName() const
{
	return TEXT("Project");
}

FText UTSSpawnSettings::GetSectionText() const
{
	return NSLOCTEXT("TankySurvivor", "SpawnSettings", "Spawn Settings");
}

FText UTSSpawnSettings::GetSectionDescription() const
{
	return NSLOCTEXT("TankySurvivor", "SpawnSettingsDescription", "Relative to spawn system for the tanky survivor project");
}
