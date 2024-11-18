// 2024 Copyright Thibault PAGERIE, Maximilien GALEA, Enguerran COBERT, Inc. All Rights Reserved.


#include "PathFinding/TDWorldPathSubsystem.h"
#include "Utils/VTDClassMacros.h"
#include "PathFinding/CPathFinder.h"
#include "PathFinding/CSparseGraph.h"
#include "World/CWorldSettings.h"
#include "World/TDWorldDelegates.h"

//UE
#include "Engine/EngineTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TDWorldPathSubsystem)

DEFINE_LOG_CATEGORY(LogWorldPathSubsystem)

UTDWorldPathSubsystem::UTDWorldPathSubsystem()
{

}

void UTDWorldPathSubsystem::OnWorldGraphInit(const ACPathFinder* InPF, const UCSparseGraph* InGraph)
{
    FTDWorldDelegates::OnWorldPathFinderCreated().Remove(m_pathfinderCreatedDelegateHandle);

    if (IsValid(GetWorld()) && IsValid(InPF) && IsValid(InGraph))
    {
        m_pathFinder = const_cast<ACPathFinder*>(InPF);

        if (m_pathFinder == NULL)
        {
            VTD_CAT_WARNING(LogWorldPathSubsystem, TEXT("[%s][%s] Can't set Path finder"), *CURRENT_CLASS, *CURRENT_FUNC);
            return;
        }

        VTD_CAT_WARNING(LogWorldPathSubsystem, TEXT("[%s][%s] World Sparse graph init"), *CURRENT_CLASS, *CURRENT_FUNC);
    }
    else
    {
        VTD_CAT_ERROR(LogWorldPathSubsystem, TEXT("[%s][%s] World:%s or PafhFinder%s or WorldGraph:s"), *CURRENT_CLASS, *CURRENT_FUNC, *GetNameSafe(GetWorld()), *GetNameSafe(InPF), *GetNameSafe(InGraph));
    }
}

bool UTDWorldPathSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    return true;
}

void UTDWorldPathSubsystem::PostInitialize()
{    
    if (GetWorld())
    {
        bool lbCanBindToDelegates = false;

        switch (GetWorld()->WorldType)
        {
        case EWorldType::Game:
        case EWorldType::PIE:
        case EWorldType::GamePreview:
            lbCanBindToDelegates = true;
            break;
        case EWorldType::Editor:
        default:
            lbCanBindToDelegates = false;
            break;
        }

        if (lbCanBindToDelegates) {
            m_pathfinderCreatedDelegateHandle = FTDWorldDelegates::OnWorldSparseGraphInitialized().AddUFunction(this, FName("OnWorldGraphInit"));
        }
    }
}

void UTDWorldPathSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    //Last Called
    VTD_CAT_ERROR(LogWorldPathSubsystem, TEXT("[%s] World Begun"), *CURRENT_CLASS);

    //TODO
    //Find base
    //Create path for all base

    if (IsValid(m_pathFinder))
    {
        //m_pathFinder->FindPath();
    }
}