// Copyright 2025 Enguerran COBERT. all right reserved.

#include "SpawnSystem/TSSpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TSSpawnVolume)

DEFINE_LOG_CATEGORY(LogSpawnVolume)

ATSSpawnVolume::ATSSpawnVolume(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer),
                                                                         SpawnVolumeSettings(), XCellSize(0),
                                                                         YCellSize(0),
                                                                         ZCellSize(0)
{
	SpawnVolumeSettings.NumXCell = 5;
	SpawnVolumeSettings.NumYCell = 5;
	SpawnVolumeSettings.NumZCell = 1;
	
	PrimaryActorTick.bCanEverTick = false;
}

void ATSSpawnVolume::DrawCells() const
{
	// Define the starting and ending points for the x-axis of the spawning volume
	const float xStart = -Brush->Bounds.BoxExtent.X;
	const float xEnd = Brush->Bounds.BoxExtent.X;

	// Define the starting and ending points for the y-axis of the spawning volume
	const float yStart = -Brush->Bounds.BoxExtent.Y;
	const float yEnd = Brush->Bounds.BoxExtent.Y;

	// Define the starting and ending points for the z-axis of the spawning volume
	// Set zStart to zero because we are considering the volume from the base
	const float zStart = 0;
	const float zEnd = Brush->Bounds.BoxExtent.Z;
	
	for (int i = 0; i < SpawnVolumeSettings.NumXCell; ++i)
	{
		float lXRatio = static_cast<float>(i) / static_cast<float>(SpawnVolumeSettings.NumXCell);
		for (int j = 0; j < SpawnVolumeSettings.NumYCell; ++j)
		{
			float lYRatio = static_cast<float>(j) / static_cast<float>(SpawnVolumeSettings.NumYCell);
			for (int k = 0; k < SpawnVolumeSettings.NumZCell; ++k)
			{
				float lZRatio = static_cast<float>(k) / static_cast<float>(SpawnVolumeSettings.NumZCell);

				// Lerp along positions base on index position of the current cell
				const float XPos = FMath::Lerp(xStart, xEnd, lXRatio) + XCellSize;
				const float YPos = FMath::Lerp(yStart, yEnd, lYRatio) + YCellSize;
				const float ZPos = FMath::Lerp(zStart, zEnd, lZRatio) + ZCellSize;

				UKismetSystemLibrary::DrawDebugBox(GetWorld(), FVector(XPos, YPos, ZPos), FVector(XCellSize, YCellSize, ZCellSize), FColor::Magenta, FRotator(), 10);
			}
		}
	}
}

void ATSSpawnVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if(GetWorld() && GetWorld()->IsEditorWorld())
	{
		if(Brush)
		{
			SetActorLocation(FVector(0,0, Brush->Bounds.BoxExtent.Z));

			XCellSize = Brush->Bounds.BoxExtent.X / SpawnVolumeSettings.NumXCell;
			YCellSize = Brush->Bounds.BoxExtent.Y / SpawnVolumeSettings.NumYCell;
			ZCellSize = Brush->Bounds.BoxExtent.Z / SpawnVolumeSettings.NumZCell;
		}
	}
}
