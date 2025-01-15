// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/WorldSettings/TSWorldSettings.h"
#include "GameFramework/Volume.h"
#include "TSSpawnVolume.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSpawnVolume, All, Log)

USTRUCT(Blueprintable, BlueprintType)
struct TANKYSURVIVOR_API FSpawnVolumeSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int32 NumXCell;
	UPROPERTY(EditAnywhere)
	int32 NumYCell;
	UPROPERTY(EditAnywhere)
	int32 NumZCell;	
};

/**
 * @class ATSSpawnVolume
 *
 * ATSSpawnVolume is a class derived from AVolume that represents a spawn volume in the game world.
 * It provides functionality to manage spawning cells within the volume based on specified settings.
 */
UCLASS()
class TANKYSURVIVOR_API ATSSpawnVolume : public AVolume
{
	GENERATED_UCLASS_BODY()
	
	/*-------------------------- MEMBERS----------------------------*/
protected:
	UPROPERTY(EditAnywhere, Category= "TS Setting", meta = (DisplayPriority = -1))
	FSpawnVolumeSettings SpawnVolumeSettings;

	UPROPERTY(VisibleInstanceOnly)
	float XCellSize;

	UPROPERTY(VisibleInstanceOnly)
	float YCellSize;

	UPROPERTY(VisibleInstanceOnly)
	float ZCellSize;
	
	/*-------------------------- FUNCTION----------------------------*/
public:
	/**
	 * Draws cells within the spawn volume based on the specified settings.
	 *
	 * This method iterates over the specified number of cells along the X, Y, and Z axes within the spawn volume.
	 * For each cell, it calculates the position based on the cell size and the cell numbers, and then draws a debug box.
	 *
	 * @note This method uses UKismetSystemLibrary::DrawDebugBox to visualize the cells.
	 */
	void DrawCells() const;

	FORCEINLINE int32 GetNumXCell() const {return SpawnVolumeSettings.NumXCell;}
	FORCEINLINE int32 GetNumYCell() const {return SpawnVolumeSettings.NumYCell;}
	FORCEINLINE int32 GetNumZCell() const {return SpawnVolumeSettings.NumZCell;}

	FORCEINLINE float GetExtendX() const {return Brush->Bounds.BoxExtent.X;}
	FORCEINLINE float GetExtendY() const {return Brush->Bounds.BoxExtent.Y;}
	FORCEINLINE float GetExtendZ() const {return Brush->Bounds.BoxExtent.Z;}

	FORCEINLINE float GetXCellSize() const {return XCellSize;}
	FORCEINLINE float GetYCellSize() const {return YCellSize;}
	FORCEINLINE float GetZCellSize() const {return ZCellSize;}
	
	/*-------------------------- OVERRIDE----------------------------*/
	//~ Begin AActor interface
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End AActor interface
};
