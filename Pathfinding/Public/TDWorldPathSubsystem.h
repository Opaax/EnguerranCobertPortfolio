// 2024 Copyright Thibault PAGERIE, Maximilien GALEA, Enguerran COBERT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "../Utils/VTDDebugMacros.h"
#include "PathFindingStructs.h"
#include "TDWorldPathSubsystem.generated.h"

VAMPIRESTD_API DECLARE_LOG_CATEGORY_EXTERN(LogWorldPathSubsystem, Log, All);

class ACPathFinder;
class AActor;

/**
* Interface where AI pawns can find their path
* 
* Contains all path from Base to another
*/
UCLASS()
class VAMPIRESTD_API UTDWorldPathSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	/* ---------------------------------- MEMBERS --------------------------------------*/
private:
	UPROPERTY()
	TObjectPtr<ACPathFinder> m_pathFinder;

	UPROPERTY();
	TMap<AActor*, FPathHandle> m_mapPath;

	FDelegateHandle m_pathfinderCreatedDelegateHandle;

	/* ---------------------------------- FUNCTIONS --------------------------------------*/
protected:
	UFUNCTION()
	void OnWorldGraphInit(const ACPathFinder* InPF, const UCSparseGraph* InGraph);

public:
	UTDWorldPathSubsystem();

	/* ---------------------------------- OVERRIDE --------------------------------------*/
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Called once all UWorldSubsystems have been initialized */
	virtual void PostInitialize() override;

	/** Called when world is ready to start gameplay before the game mode transitions to the correct state and call BeginPlay on all actors */
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
