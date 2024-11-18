// Fill out your copyright notice in the Description page of Project Settings.

#include "PathFinding/CSparseGraph.h"
#include "Utils/VTDDebugMacros.h"
#include "Tiles/CTile.h"
#include "PathFinding/CPathFindingNode.h"
#include "PathFinding/PathFindingComponentOwner.h"
#include "Utils/TDAlgo.h"
#include "DevSettings/CDeveloperSettings.h"
#include "PathFinding/CPathEdge.h"

#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CSparseGraph)

int32 UCSparseGraph::m_invalidID = -1;

UCSparseGraph::UCSparseGraph(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	bIsInitialized = false;
}

void UCSparseGraph::FindNodesInWorld()
{
	if (!IsValid(GetWorld())) {
		return;
	}

	for (TActorIterator<ACTile> lTileItr(GetWorld()); lTileItr; ++lTileItr)
	{
		ACTile* lTile = *lTileItr;
		if (IsValid(lTile)) {
			if (UCPathFindingNode* lNodeComp = IPathFindingComponentOwner::Execute_GetPathFindingNodeComponent(lTile))
			{
				//Add node only if walkable, this will optimize the find algo
				if (lNodeComp->IsWalkable())
				{
					AddNode(lNodeComp);
				}
			}
		}
	}
}

void UCSparseGraph::SortNodes()
{
	if (m_allNodes.IsEmpty())
	{
		return;
	}

	m_allNodes.Sort(FPFNodeTopLeftToBottomRight());

	ReorderNodesID();
}

void UCSparseGraph::ReorderNodesID()
{
	if (m_allNodes.IsEmpty())
	{
		return;
	}

	int32 lID = 0;
	for (auto* lNode : m_allNodes)
	{
		if (IsValid(lNode))
		{
			lNode->SetID(lID++);
		}
	}
}

void UCSparseGraph::FindRegisterEdgeTo(const int32 Index)
{
	if (UCPathFindingNode* lNode = GetNode(Index)) {
		//Check if node is node Pending kill or flag that can invalide it
		if (IsValid(lNode))
		{
			//Get some dev setting in order to get right edges
			const UCDeveloperSettings* lDevSetting	= GetDefault<UCDeveloperSettings>();
			const float lCellSize					= lDevSetting->BaseCellSize;
			const FVector lNodeLoc					= lNode->GetNodeLocation();

			//Cached some location where neighbour should be located
			const FVector lUpEdgeLoc	= FVector(lNodeLoc.X, lNodeLoc.Y + lCellSize, lNodeLoc.Z);
			const FVector lLeftEdgeLoc	= FVector(lNodeLoc.X - lCellSize, lNodeLoc.Y, lNodeLoc.Z);
			const FVector lDownEdgeLoc	= FVector(lNodeLoc.X, lNodeLoc.Y - lCellSize, lNodeLoc.Z);
			const FVector lRightEdgeLoc = FVector(lNodeLoc.X + lCellSize, lNodeLoc.Y, lNodeLoc.Z);

			//Temp array that will be appended when all neighbour has been checked
			TArray<UCPathEdge*> lEdges;

			for (UCPathFindingNode* lNodeCheck : m_allNodes)
			{
				if (lNodeCheck && IsValid(lNodeCheck))
				{
					//Do not check if him
					if (lNodeCheck == lNode)
					{
						continue;
					}

					const FVector lCheckLoc = lNodeCheck->GetNodeLocation();

					if (lCheckLoc.X == lLeftEdgeLoc.X || lCheckLoc.X == lRightEdgeLoc.X 
						|| lCheckLoc.Y == lUpEdgeLoc.Y || lCheckLoc.Y == lDownEdgeLoc.Y)
					{
						//check if the distance is over Cell size, if not is a Neighbour
						if (FVector::Distance(lNodeLoc, lCheckLoc) <= lCellSize)
						{
							if (UCPathEdge* lEdge = UCPathEdge::GetNewEdges(lNode))
							{
								lEdge->SetFrom(Index);
								lEdge->SetTo(lNodeCheck->GetID());
								lEdge->SetCost(FVector::DistSquared(lNodeLoc, lCheckLoc));

								lEdges.Add(lEdge);
							}
						}
					}
				}
			}

			CheckAppendEdges(Index, lEdges);
		}
	}
}

void UCSparseGraph::CheckAppendEdges(const int32 Index, const TArray<UCPathEdge*> Edges)
{
	FEdgesHandle lHandle = FEdgesHandle(Edges);

	if (m_allEdges.Contains(Index))
	{
		m_allEdges[Index] = lHandle;
	}
	else
	{
		m_allEdges.Add(Index, lHandle);
	}
}

void UCSparseGraph::Init()
{
	FindNodesInWorld();
	SortNodes();

	for (int32 i = 0; i < m_allNodes.Num(); i++)
	{
		FindRegisterEdgeTo(i);
	}

	bIsInitialized = true;
}

bool UCSparseGraph::RemoveNode(const int32 Index)
{
	if (UCPathFindingNode* lNode = GetNode(Index)) {
		m_allNodes.RemoveAt(lNode->GetID());

		for (int32 i = 0; i < m_allNodes.Num(); i++) {
			m_allNodes[i]->SetID(i);
		}

		m_nextValidID = m_allNodes.Num();

		return true;
	}

	return false;
}

bool UCSparseGraph::AddNode(UCPathFindingNode* Node)
{
	checkf(Node != nullptr, TEXT("[%s::%s], trying to add null Node"), *CURRENT_CLASS, *CURRENT_FUNC);

	if (IsValid(Node)) {
		Node->SetID(m_allNodes.Add(Node));
		m_nextValidID = m_allNodes.Num();

		return true;
	}

	return false;
}

void UCSparseGraph::ShowNodeInfos(bool ShowNode)
{
	if (m_allNodes.IsEmpty())
	{
		VTDPFNode_ERROR(TEXT("[%s] can't show node, there is no node registered yet"), *CURRENT_CLASS);
		return;
	}

	for (auto* lNode : m_allNodes)
	{
		if (IsValid(lNode))
		{
			lNode->ShowInfos(ShowNode);
		}
	}
}

void UCSparseGraph::DrawNodeEdges(int32 Index, float Time)
{
	if (m_allNodes.IsEmpty())
	{
		VTDPFNode_ERROR(TEXT("[%s] can't Draw Node Edges, there is no node registered yet"), *CURRENT_CLASS);
		return;
	}

	if (m_allEdges.Contains(Index))
	{
		UCPathFindingNode* lFrom	= nullptr;
		UCPathFindingNode* lTo		= nullptr;
		for (UCPathEdge* lEdge : m_allEdges[Index].AllEdges)
		{
			lFrom = GetNode(lEdge->GetFrom());
			lTo = GetNode(lEdge->GetTo());

			if (lFrom && lTo)
			{
				//Up loc to avoid draw overlap
				FVector lFromLoc = lFrom->GetNodeLocation() + FVector(0, 0, 10);
				FVector lToLoc = lTo->GetNodeLocation() + FVector(0, 0, 10);

				DRAW_ARROW_TIME(lFromLoc, lToLoc, FColor::Red, Time);
			}
		}
	}
	else
	{
		VTDPFNode_ERROR(TEXT("[%s] can't Draw Node Edges, there is no edges at [%d]"), *CURRENT_CLASS, Index);
	}
}

UCPathFindingNode* UCSparseGraph::GetNode(const int32 Index)
{
	if (Index < m_allNodes.Num() && Index != m_invalidID) {
		return m_allNodes[Index];
	}

	return nullptr;
}

FVector UCSparseGraph::GetNodeLocation(const int32 Index)
{
	if (UCPathFindingNode* lNode = GetNode(Index))
	{
		return lNode->GetNodeLocation();
	}
	return FVector();
}

bool UCSparseGraph::GetEdgesForIndex(int32 Index, FEdgesHandle& OutHandleEdges)
{
	if (m_allEdges.Contains(Index))
	{
		OutHandleEdges = m_allEdges[Index];
		return true;
	}

	return false;
}

void UCSparseGraph::PostInitProperties()
{
	Super::PostInitProperties();

	m_nextValidID = m_allNodes.Num();
}
