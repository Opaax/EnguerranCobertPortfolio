// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinding/CPathFindingNode.h"
#include "World/CWorldSettings.h"
#include "PathFinding/CSparseGraph.h"
#include "Utils/VTDDebugMacros.h"

//UE
#include "Components/TextRenderComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CPathFindingNode)

int32 UCPathFindingNode::m_invalidID = -1;
FVector UCPathFindingNode::m_offsetNodeLocation = FVector(0,0,50.f);

UCPathFindingNode::UCPathFindingNode(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UCPathFindingNode::ShowInfos(bool ShowInfo)
{
	if (ShowInfo && IsValid(GetOwner()))
	{
		UTextRenderComponent* lTextRend = Cast<UTextRenderComponent>(GetOwner()->AddComponentByClass(UTextRenderComponent::StaticClass(), false, FTransform(), false));

		if (IsValid(lTextRend))
		{
			lTextRend->SetWorldLocationAndRotation(m_nodeLocation, FRotator(0, 180.f, 0));
			lTextRend->SetText(FText::FromString(FString::FromInt(GetID())));
			lTextRend->SetTextRenderColor(FColor::Red);
		}
	}
	else if (IsValid(GetOwner()))
	{
		if (UTextRenderComponent* lTextRend = Cast<UTextRenderComponent>(GetOwner()->GetComponentByClass(UTextRenderComponent::StaticClass())))
		{
			lTextRend->DestroyComponent();
		}
	}
}

bool UCPathFindingNode::IsWalkable() const
{
	return EnumHasAllFlags(m_nodeFlags, EPathFindingNodeFlags::Walkable);
}

void UCPathFindingNode::InitializeComponent()
{
	if (GetOwner()) {
		m_nodeLocation = GetOwner()->GetActorLocation() + m_offsetNodeLocation;
	}

	Super::InitializeComponent();
}