// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinding/CPathFinder.h"
#include "PathFinding/CSparseGraph.h"
#include "PathFinding/PathFindingStructs.h"
#include "PathFinding/CPathEdge.h"
#include "PathFinding/CPathFindingNode.h"
#include "Utils/VTDDebugMacros.h"

//UE
#include "Containers/ContainerAllocationPolicies.h"
#include "HAL/IConsoleManager.h"
#include "Utils/TDIndexedPriorityQLow.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CPathFinder)

//Global var
int32 GShowPathWhenFindPath = 0;

static FAutoConsoleVariableRef CVarShowPathWhenFindPath(
    TEXT("TD.ShowPathWhenFindPath"),
    GShowPathWhenFindPath,
    TEXT("show the path when the Pathfinder FindPath is called\n")
    TEXT("   0: Path not show\n")
    TEXT("   1: Path show\n"));

FName ACPathFinder::WorldGraphName = FName("WorldGraph");

ACPathFinder::ACPathFinder(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{	
	m_worldGraph = CreateDefaultSubobject<UCSparseGraph>(WorldGraphName);

	PrimaryActorTick.bCanEverTick = false;
}

void ACPathFinder::InitPathFinder()
{
	if (IsValid(m_worldGraph))
	{
		m_worldGraph->Init();
        bIsInit = true;
	}
}

void ACPathFinder::ShowNodeInfo(bool ShowNode) const
{
    if (IsValid(m_worldGraph))
    {
        m_worldGraph->ShowNodeInfos(ShowNode);
    }
}

void ACPathFinder::DrawNodeEdges(int32 Index, float Time) const
{
    if (IsValid(m_worldGraph))
    {
        m_worldGraph->DrawNodeEdges(Index, Time);
    }
}

void ACPathFinder::FindPath(int32 From, int32 To, FPathHandle& OutPathHandle)
{
	if (!m_worldGraph)
	{
		return;
	}

	const int32 lNodesNums = m_worldGraph->GetNodeNum();

    m_shortPath.Init(nullptr,lNodesNums);
    m_searchFrontier.Init(nullptr, lNodesNums);
    m_globalCost.Init(0, lNodesNums);
    m_FCost.Init(0, lNodesNums);

    TDIndexedPriorityQLow<float> PriorityQueue(m_FCost, lNodesNums);

	PriorityQueue.Insert(From);

    //while the queue is not empty
    while (!PriorityQueue.IsEmpty())
    {
        //get lowest cost node from the queue
        int lNextClosestNode = PriorityQueue.Pop();

        //move this node from the frontier to the spanning tree
        m_shortPath[lNextClosestNode] = m_searchFrontier[lNextClosestNode];

        //if the target has been found exit
        if (lNextClosestNode == To)
        {
            FPathHandle lPath;

            int32 lNodeID = To;

            lPath.Path.Add(lNodeID);

            while ((lNodeID != From) && (m_shortPath[lNodeID] != 0))
            {
                lNodeID = m_shortPath[lNodeID]->GetFrom();

                lPath.Path.Insert(lNodeID, 0);
            }

            //Debug
            if (GShowPathWhenFindPath > 0)
            {
                UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());

                int32 lPrevID = lPath.Path[0];
                for (int32 i = 1; i < lPath.Path.Num(); i++)
                {
                    int32 lCurrentID = lPath.Path[i];

                    //Up loc to avoid draw overlap
                    FVector lFromLoc = m_worldGraph->GetNode(lPrevID)->GetNodeLocation() + FVector(0, 0, 10);
                    FVector lToLoc = m_worldGraph->GetNode(lCurrentID)->GetNodeLocation() + FVector(0, 0, 10);


                    DRAW_ARROW_TIME_SIZE(lFromLoc, lToLoc, FColor::Red, 1000.f, 2.f);

                    if (i == 1)
                    {
                        DRAW_SPHERE_AT_COLOR(lFromLoc, 1000.f, FColor::Green);
                    }
                    else if (i == lPath.Path.Num() - 1)
                    {
                        DRAW_SPHERE_AT_COLOR(lToLoc, 1000.f, FColor::Blue);
                    }

                    lPrevID = lCurrentID;
                }
            }

            return;
        }

        FEdgesHandle lHandleEdges;

        if (m_worldGraph->GetEdgesForIndex(lNextClosestNode, lHandleEdges))
        {
            for (UCPathEdge* lEdge : lHandleEdges.AllEdges)
            {
                //use squared avoid sqrt
                float lCostToTarget = FVector::DistSquared(m_worldGraph->GetNodeLocation(lEdge->GetTo()), m_worldGraph->GetNodeLocation(To));
                float lCost = lEdge->GetCost();
                float lGCost = m_globalCost[lNextClosestNode] + lCost;

                if (m_searchFrontier[lEdge->GetTo()] == nullptr)
                {
                    m_FCost[lEdge->GetTo()] = lGCost + lCostToTarget;
                    m_globalCost[lEdge->GetTo()] = lGCost;

                    PriorityQueue.Insert(lEdge->GetTo());

                    m_searchFrontier[lEdge->GetTo()] = lEdge;
                }
                else if ((lGCost < m_globalCost[lEdge->GetTo()]) && (m_shortPath[lEdge->GetTo()] == nullptr))
                {
                    m_FCost[lEdge->GetTo()] = lGCost + lCostToTarget;
                    m_globalCost[lEdge->GetTo()] = lGCost;

                    PriorityQueue.ChangePriority(lEdge->GetTo());

                    m_searchFrontier[lEdge->GetTo()] = lEdge;
                }
            }
        }
    }
}
