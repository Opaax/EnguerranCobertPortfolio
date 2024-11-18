// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinding/PathFindingComponentOwner.h"
#include "PathFinding/CPathFindingNode.h"

UCPathFindingNode* IPathFindingComponentOwner::GetPathFindingNodeComponent_Implementation()
{
    if (IsValid(m_pfNode)) {
        return m_pfNode;
    }

    if (IsValid(GetActorOwner())) {
        m_pfNode = GetActorOwner()->FindComponentByClass<UCPathFindingNode>();
    }

    return m_pfNode;
}

bool IPathFindingComponentOwner::IsWalkable_Implementation()
{
    //if pf node is not set yet set it
    if (!IsValid(m_pfNode)) 
    {
        Execute_GetPathFindingNodeComponent(GetActorOwner());
    }
    
    if (IsValid(m_pfNode))
    {
        return m_pfNode->IsWalkable();
    }

    return false;
}
