// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpatialHashingHandler.h"
#include "TSSpawnLocationActor.h"
#include "Subsystems/WorldSubsystem.h"
#include "TSSpawnSubsystem.generated.h"

class ATSSpawnVolume;
class ATSSpawnLocationActor;

DECLARE_LOG_CATEGORY_EXTERN(LogSpawnSubsystem, All, Log)

struct FSpawnGridHandle : public FSpawnGridHandleBase
{
	ATSSpawnLocationActor* SpawnActor;

	void SetSpawnActor(ATSSpawnLocationActor* InSpawnActor)
	{
		check(InSpawnActor);
		SpawnActor = InSpawnActor;
		Location = SpawnActor->GetActorLocation();
	}

	FSpawnGridHandle(): SpawnActor(nullptr) {}
	~FSpawnGridHandle(){SpawnActor = nullptr;}
};

/**
 * @class UTSSpawnSubsystem
 *
 * Class that serves as a subsystem for handling spawning and managing actor locations within a world.
 * It inherits from UWorldSubsystem.
 */
UCLASS()
class TANKYSURVIVOR_API UTSSpawnSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	/*-------------------------- MEMBERS ----------------------------*/
private:
	SpatialHashingHandler<FSpawnGridHandle>* SpawnGridHandle;

	/*-------------------------- FUNCTION ----------------------------*/
protected:
	/**
	 * Create and spawn actor locations based on the provided world settings.
	 * This method is responsible for generating spawn locations within the defined volume.
	 *
	 * @param InWorld The reference to the world where the actor locations will be spawned.
	 */
	void CreateSpawnActorLocation(const UWorld& InWorld) const;
	/**
	 * Create a spawn grid based on the provided spawn volume.
	 * Create the grid that hold data for performing search of the grid (i.e. SpawnGridHandle)
	 * @param SpawnVolume The spawn volume used to define the grid structure.
	 */
	void CreateSpawnGrid(const ATSSpawnVolume* SpawnVolume) const;

	/**
	 * Get all actors within a specified sphere from the provided query location.
	 *
	 * @param QueryLocation The center location of the sphere to search for actors.
	 * @param QuaryRadius The radius of the sphere around the query location to search for actors.
	 * @param OutActors An array of AActor pointers to store the actors found within the sphere.
	 * @return The number of actors found within the specified sphere.
	 */
	int32 GetSpawnInSphere(FVector QueryLocation, float QuaryRadius, TArray<AActor*>& OutActors) const;
	
public:
	UTSSpawnSubsystem();

	/**
	 * Get spawn locations within a given distance range from the player location.
	 *
	 * @param PlayerLocation The location of the player in the world.
	 * @param MinDist The minimum distance from the player for a spawn location to be considered.
	 * @param MaxDist The maximum distance from the player for a spawn location to be considered.
	 * @param OutSpawns An array of ATSSpawnLocationActor pointers to store the spawn locations found within the distance range.
	 */
	UFUNCTION(BlueprintCallable, Category= "TSSpawnSubsystem")
	void GetSpawnLocationForDistance(const FVector PlayerLocation, const float MinDist, const float MaxDist, TArray<ATSSpawnLocationActor*>& OutSpawns);
	
	/*-------------------------- OVERRIDE ----------------------------*/
public:
	//~ Begin USubsystem interface
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End USubsystem interface
};
