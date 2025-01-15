// Copyright 2025 Enguerran COBERT. all right reserved.

#include "SpawnSystem/TSSpawnManagerComponent.h"

#include "Engine/AssetManager.h"
#include "Framework/TankySurvivorUtils.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnSystem/TSSpawnLocationActor.h"
#include "SpawnSystem/TSSpawnSettings.h"
#include "SpawnSystem/TSSpawnSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TSSpawnManagerComponent)

UTSSpawnManagerComponent::UTSSpawnManagerComponent(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer), SpawnDefinition(nullptr)
{
	bWantsInitializeComponent = true;
}

void UTSSpawnManagerComponent::SpawnTest(float MinDist, float MaxDist, UClass* SpawnClass) const
{
	if(UTSSpawnSubsystem* lSSub = GetWorld()->GetSubsystem<UTSSpawnSubsystem>())
	{
		APawn* lPlayerPawn = UGameplayStatics::GetPlayerController(GetWorld(),0)->GetPawn();
		check(lPlayerPawn);
		TArray<ATSSpawnLocationActor*> OutSpawns;
		lSSub->GetSpawnLocationForDistance(lPlayerPawn->GetActorLocation(), MinDist, MaxDist,OutSpawns);

		//TODO Check player movement forward/backward camera view

		ATSSpawnLocationActor* OutSpawn = nullptr;
		int32 OutIndex = -1;
		TankySurvivorUtils::TSArray_Random(OutSpawns, OutSpawn,OutIndex);
		if(ensure(OutSpawn))
		{
			FTransform lTransform{OutSpawn->GetTransform()};
			FActorSpawnParameters lParams;
			lParams.ObjectFlags = RF_Transient;
			lParams.Owner = GetOwner();
		
			GetWorld()->SpawnActor<AActor>(SpawnClass,lTransform,lParams);
		}
	}
}

void UTSSpawnManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UTSSpawnSettings* lSetting = GetMutableDefault<UTSSpawnSettings>();
	check(lSetting);

	UAssetManager& AssetManager = UAssetManager::Get();
	FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(lSetting->GetSpawnDefinition());
	TSubclassOf<UTSSpawnDefinition> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	check(AssetClass);
	SpawnDefinition = const_cast<UTSSpawnDefinition*>(GetDefault<UTSSpawnDefinition>(AssetClass));
}

void UTSSpawnManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	check(SpawnDefinition);

	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;
	
	TimerDel.BindUFunction(this, FName("SpawnTest"), SpawnDefinition->GetMinDistance(), SpawnDefinition->GetMaxDistance(), SpawnDefinition->GetSpawnable());
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, SpawnDefinition->GetSpawnRate(), true);
}
