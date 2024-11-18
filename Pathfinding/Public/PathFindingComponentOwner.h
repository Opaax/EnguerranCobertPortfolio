// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PathFindingComponentOwner.generated.h"

class UCPathFindingNode;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPathFindingComponentOwner : public UInterface
{
	GENERATED_BODY()
};

/**
 * handy function to override to communicate with Path Node passing trough the actor that contains that node
 */
class VAMPIRESTD_API IPathFindingComponentOwner
{
	GENERATED_BODY()

	TObjectPtr<UCPathFindingNode> m_pfNode;
public:
	virtual AActor* GetActorOwner() const = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCPathFindingNode* GetPathFindingNodeComponent();
	virtual UCPathFindingNode* GetPathFindingNodeComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsWalkable();
	virtual bool IsWalkable_Implementation();
};
