// Copyright 2025 Enguerran COBERT. all right reserved.

#include "SpawnSystem/TSSpawnLocationActor.h"
#include "Framework/DebugMacro.h"
#include "WorldPartition/WorldPartitionRuntimeSpatialHash.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TSSpawnLocationActor)

ATSSpawnLocationActor::ATSSpawnLocationActor(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Visual =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Visual->SetupAttachment(Root);
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Visual->SetStaticMesh(SphereMeshAsset.Object);
	Visual->SetHiddenInGame(true);
	Visual->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	PrimaryActorTick.bCanEverTick = false;
}
