// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Utils/VTDClassMacros.h"
#include "CPathFinder.generated.h"

class UCSparseGraph;
class UCPathEdge;
struct FPathHandle;

UCLASS()
class VAMPIRESTD_API ACPathFinder : public AActor
{
	GENERATED_UCLASS_BODY()

	/* ---------------------------------- MEMBERS --------------------------------------*/
protected:
	UPROPERTY(VisibleInstanceOnly, Category = PathFinding, meta = (DisplayName = "WorldGraph"))
	TObjectPtr<UCSparseGraph> m_worldGraph;

    UPROPERTY(VisibleInstanceOnly, Category = PathFinding, meta = (DisplayName = "IsInit"))
    bool bIsInit;

    typedef TArray<float>       TFloatArray;
    typedef TArray<UCPathEdge*> TPathEdgeArray;

    TPathEdgeArray m_shortPath;
    TPathEdgeArray m_searchFrontier;
    TFloatArray    m_globalCost;
    TFloatArray    m_FCost;

public:
	static FName WorldGraphName;

	/* ---------------------------------- FUNCTION --------------------------------------*/
public:
	UFUNCTION(Category = "PathFinder")
	void InitPathFinder();

	UFUNCTION(Category = "PathFinder")
	void ShowNodeInfo(bool ShowNode) const;

	UFUNCTION(Category = "PathFinder")
	void DrawNodeEdges(int32 Index, float Time) const;
	
	UFUNCTION(Category = "PathFinder")
	void FindPath(int32 From, int32 To, FPathHandle& OutPathHandle);

	FORCEINLINE DECLARE_GETTER(WorldGraph, m_worldGraph, UCSparseGraph*);
	FORCEINLINE DECLARE_GETTER(IsInit, bIsInit, bool);
	/* ---------------------------------- OVERRIDE --------------------------------------*/
};