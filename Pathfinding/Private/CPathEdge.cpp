// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinding/CPathEdge.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CPathEdge)

UCPathEdge::UCPathEdge(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

UCPathEdge* UCPathEdge::GetNewEdges(UObject* Outer)
{
    return NewObject<UCPathEdge>(Outer);
}
