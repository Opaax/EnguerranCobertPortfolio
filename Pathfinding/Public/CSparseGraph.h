// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Utils/VTDClassMacros.h"
#include "PathFindingStructs.h"
#include "CSparseGraph.generated.h"

class UCPathFindingNode;
class UCPathEdge;

/**
 * Sparse Graph
 * 
 * Contains All nodes in the world.
 */
UCLASS(ClassGroup = (PathFinding), BlueprintType, Blueprintable)
class VAMPIRESTD_API UCSparseGraph : public UObject
{
	GENERATED_UCLASS_BODY()
	
	static int32 m_invalidID;

	/* ---------------------------------- MEMBERS --------------------------------------*/
private:
	int32 m_nextValidID = 0;

	UPROPERTY(VisibleInstanceOnly, meta = (DisplayName = "AllNodes"))
	TArray<UCPathFindingNode*> m_allNodes;

	UPROPERTY(VisibleInstanceOnly, meta = (DisplayName = "AllNodes"))
	TMap<int32, FEdgesHandle> m_allEdges;

	uint8 bIsInitialized = 0;

	/* ---------------------------------- FUNCTION --------------------------------------*/
protected:
	UFUNCTION()
	void FindNodesInWorld();

	/* Sort Nodes From Top Left to Bottom Right*/
	UFUNCTION()
	void SortNodes();

	/* After sort we need to give Incorrect ID since the sort can move on array Nodes, automatically called on 'SortNodes'*/
	UFUNCTION()
	void ReorderNodesID();

	/*
	* Check if the node has any neighbour 
	* if yes, register them into edges map
	* 
	* @ID: the Node ID that we want to check
	*/
	UFUNCTION()
	void FindRegisterEdgeTo(const int32 ID);

	/* 
	* Edges are store in a map
	* Map entry is Node Id
	* Map value is an Array of edges
	*/
	UFUNCTION()
	void CheckAppendEdges(const int32 Index, const TArray<UCPathEdge*> Edges);

public:
	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	void Init();

	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	bool RemoveNode(const int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	bool AddNode(UCPathFindingNode* Node);

	/*
	* Toggle the node infos such as ID
	*/
	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	void ShowNodeInfos(bool ShowNode);

	/* 
	* Draw all edge of an node
	* 
	* @ID: Node ID
	* @Time: how long debug will stay on world
	*/
	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	void DrawNodeEdges(int32 ID, float Time);

	/*
	* Get the node component at certain ID
	* 
	* @ID: The node ID
	*/
	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	UCPathFindingNode* GetNode(const int32 ID);

	/* Safe return location, return FVector(0,0,0) if node is NULL*/
	UFUNCTION(BlueprintCallable, Category = SparseGraph)
	FVector GetNodeLocation(const int32 ID);

	UFUNCTION(BlueprintCallable,Category = SparseGraph, meta = (DisplayName = "GetNodes"))
	void GetNodesRef(TArray<UCPathFindingNode*>& OutNodes) const { OutNodes = m_allNodes; };

	bool GetEdgesForIndex(int32 Index, FEdgesHandle& OutHandleEdges);

	FORCEINLINE DECLARE_GETTER(IsInitialized, (bool)bIsInitialized, bool);
	FORCEINLINE DECLARE_GETTER(GetNodes, m_allNodes, TArray<UCPathFindingNode*>);
	FORCEINLINE DECLARE_GETTER(NodeNum, m_allNodes.Num(), int32);

	/* ---------------------------------- OVERRIDE --------------------------------------*/
public:
	virtual void PostInitProperties() override;
};
