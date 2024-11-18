// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Utils/VTDClassMacros.h"
#include "PathFindingEnums.h"
#include "CPathFindingNode.generated.h"


/*
* Node in Tile
* 
* Contains all infos for path finding for the Tile
*/
UCLASS( ClassGroup=(PathFinding), meta=(BlueprintSpawnableComponent) )
class VAMPIRESTD_API UCPathFindingNode : public UActorComponent
{
	GENERATED_UCLASS_BODY()
	
	static int32 m_invalidID;
	static FVector m_offsetNodeLocation;

	/* ---------------------------------- MEMBERS --------------------------------------*/
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Debug", AdvancedDisplay)
	int32 m_ID = m_invalidID;

	UPROPERTY(VisibleInstanceOnly, Category = "Debug", AdvancedDisplay)
	FVector m_nodeLocation;
	
	/* 
	* Node flag to control node to be register or not on graph
	* 
	* Should be set in CTOR by its owner
	*/
	UPROPERTY(VisibleAnywhere, meta = (Bitmask, BitmaskEnum = EPathFindingNodeFlags, DisplayName = "NodeFlags"))
	EPathFindingNodeFlags m_nodeFlags = EPathFindingNodeFlags::None;

	/* ---------------------------------- FUNCTION --------------------------------------*/
public:
	UFUNCTION(BlueprintCallable, Category = "PFNode")
	void ShowInfos(bool ShowInfo);

	UFUNCTION(BlueprintCallable, Category = "PFNode", meta = (DisplayName = "SetNodeFlags"))
	void BP_SetNodeFlags(EPathFindingNodeFlags InFlags) { SetNodeFlags(InFlags); }

	UFUNCTION(BlueprintCallable, Category = "PFNode", meta = (DisplayName = "IsWalkable"))
	bool IsWalkable() const;

	FORCEINLINE DECLARE_GETTER_SETTER(ID, m_ID, int32);
	FORCEINLINE DECLARE_GETTER_SETTER(NodeLocation, m_nodeLocation, FVector);
	FORCEINLINE DECLARE_GETTER_SETTER(NodeFlags, m_nodeFlags, EPathFindingNodeFlags);

	/* ---------------------------------- OVERRIDE --------------------------------------*/
public:
	virtual void InitializeComponent() override;
};
