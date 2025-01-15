// Copyright 2025 Enguerran COBERT. all right reserved.

#include "SpawnSystem/TSSpawnSubsystem.h"

#include "Framework/DebugMacro.h"
#include "Framework/WorldSettings/TSWorldSettings.h"
#include "SpawnSystem/TSSpawnLocationActor.h"
#include "SpawnSystem/TSSpawnVolume.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TSSpawnSubsystem)

DEFINE_LOG_CATEGORY(LogSpawnSubsystem)

UTSSpawnSubsystem::UTSSpawnSubsystem(): SpawnGridHandle(nullptr) {}

void UTSSpawnSubsystem::GetSpawnLocationForDistance(const FVector PlayerLocation, const float MinDist,
                                                    const float MaxDist, TArray<ATSSpawnLocationActor*>& OutSpawns)
{
	if(SpawnGridHandle && SpawnGridHandle->GetGrid())
	{
		if(SpawnGridHandle->GetHandlesRef().IsEmpty())
		{
			return;
		}
		
		TArray<AActor*> OutActors;
		GetSpawnInSphere(PlayerLocation, MaxDist,OutActors);

		const float MinDistSq = MinDist * MinDist;
		for (int i = OutActors.Num() - 1; i >= 0; --i)
		{
			AActor* lOutActor = OutActors[i];

			//Check if the actor is really a Spawn Location
			if(ATSSpawnLocationActor* lSpawn = Cast<ATSSpawnLocationActor>(lOutActor))
			{
				//Check if the spawn is in range, add to outspawn if true
				if(FVector::DistSquared(PlayerLocation, lSpawn->GetActorLocation()) > MinDistSq)
				{
					OutSpawns.Add(lSpawn);
				}
			}
		}
	}
}

void UTSSpawnSubsystem::CreateSpawnActorLocation(const UWorld& InWorld) const
{
	if(ATSWorldSettings* lWS = CastChecked<ATSWorldSettings>(InWorld.GetWorldSettings(), ECastCheckedType::NullChecked))
	{
		//Look for the volume
		if(ATSSpawnVolume* lVolume = lWS->GetSpawnVolume())
		{
			UClass* lLocationClass = lWS->GetSpawnLocationClass();

			if(!lLocationClass)
			{
				//Set default location class if Null
				lLocationClass = ATSSpawnLocationActor::StaticClass();
			}

			//Create the grid
			CreateSpawnGrid(lVolume);
			
			const int32 XNum = lVolume->GetNumXCell();
			const int32 YNum = lVolume->GetNumYCell();
			const int32 ZNum = lVolume->GetNumZCell();
			const int32 lTotalNum = XNum * YNum * ZNum;

			SpawnGridHandle->Reserve(lTotalNum);

			//Define spawn bounds
			const float xEnd = lVolume->GetExtendX();
			const float xStart = -xEnd;
			const float yEnd = lVolume->GetExtendY();
			const float yStart = -yEnd;
			const float zStart = 0;
			const float zEnd = lVolume->GetExtendZ();
	
			for (int i = 0; i < XNum; ++i)
			{
				float lXRatio = static_cast<float>(i) / static_cast<float>(XNum);
				for (int j = 0; j < YNum; ++j)
				{
					float lYRatio = static_cast<float>(j) / static_cast<float>(YNum);
					for (int k = 0; k < ZNum; ++k)
					{
						float lZRatio = static_cast<float>(k) / static_cast<float>(ZNum);
				
						const float XPos = FMath::Lerp(xStart, xEnd, lXRatio) + lVolume->GetXCellSize();
						const float YPos = FMath::Lerp(yStart, yEnd, lYRatio) + lVolume->GetYCellSize();
						const float ZPos = FMath::Lerp(zStart, zEnd, lZRatio) + lVolume->GetZCellSize();

						//Define params for the Spawn location
						FTransform lSpawnTrans{FQuat(),FVector(XPos, YPos, ZPos), FVector::One()};
						FActorSpawnParameters lParams;
						lParams.ObjectFlags = RF_Transient;

						//Create the handle for the Grid
						FSpawnGridHandle* lHandle = new FSpawnGridHandle();
						lHandle->SetSpawnActor(GetWorld()->SpawnActor<ATSSpawnLocationActor>(lLocationClass, lSpawnTrans, lParams));

						SpawnGridHandle->AddHandle(lHandle);
					}
				}
			}
			
		}else
		{
			TANKY_ERROR_CAT(LogSpawnSubsystem, TEXT("[%s] do not found any spawn volume"), *CURRENT_CLASS);
		}
		
	}else
	{
		TANKY_ERROR_CAT(LogSpawnSubsystem, TEXT("[%s] do not found world setting of type: %s"), *CURRENT_CLASS, *GetNameSafe(ATSWorldSettings::StaticClass()));
	}
}

void UTSSpawnSubsystem::CreateSpawnGrid(const ATSSpawnVolume* SpawnVolume) const
{
	check(SpawnVolume);
	check(SpawnGridHandle);
	
	const int32 XSize = SpawnVolume->GetXCellSize();
	const int32 YSize = SpawnVolume->GetYCellSize();
			
	const int32 lFinalSize = FMath::Max(XSize,YSize);

	//TODO Full custom grid with cell size not base on cube?
	SpawnGridHandle->CreateGrid(lFinalSize, -1);
}

int32 UTSSpawnSubsystem::GetSpawnInSphere(FVector QueryLocation, float QuaryRadius, TArray<AActor*>& OutActors) const
{
	if(SpawnGridHandle == nullptr || SpawnGridHandle->GetGrid() == nullptr)
	{
		return -1;
	}

	TArray<int32> lIndexes;

	//Get all spawn in radius
	int32 lOutNumberFound = SpawnGridHandle->GetGrid()->FindPointsInBall(QueryLocation, QuaryRadius,[this, &QueryLocation](const int& VID)->double
	{
		return FVector3d::DistSquared(QueryLocation,SpawnGridHandle->GetHandlesRef().IsValidIndex(VID) && SpawnGridHandle->GetHandlesRef()[VID]->SpawnActor ? SpawnGridHandle->GetHandlesRef()[VID]->SpawnActor->GetActorLocation()
			: FVector(0, 0,0));
	}, lIndexes);

	//Fill up outactor array
	for (auto& lIndex : lIndexes)
	{
		if(SpawnGridHandle->GetHandlesRef().IsValidIndex(lIndex))
		{
			OutActors.Add(SpawnGridHandle->GetHandlesRef()[lIndex]->SpawnActor);
		}
	}

	return lOutNumberFound;
}

void UTSSpawnSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	CreateSpawnActorLocation(InWorld);
	
	Super::OnWorldBeginPlay(InWorld);
}

void UTSSpawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	SpawnGridHandle = new SpatialHashingHandler<FSpawnGridHandle>();
	
	Super::Initialize(Collection);
}

void UTSSpawnSubsystem::Deinitialize()
{
	if(SpawnGridHandle)
	{
		SpawnGridHandle->FlushGrid();
		delete SpawnGridHandle;
	}
	
	Super::Deinitialize();
}
