// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Utils/VTDClassMacros.h"
#include "CPathEdge.generated.h"

/**
 * Contains information for a edge path from a tile to another one
 */
UCLASS()
class VAMPIRESTD_API UCPathEdge : public UObject
{
	GENERATED_UCLASS_BODY()
	
	/* ---------------------------------- MEMBERS --------------------------------------*/
private:
	UPROPERTY()
	int32 m_from = -1;

	UPROPERTY()
	int32 m_to = -1;

	UPROPERTY()
	float m_cost = -1;

	/* ---------------------------------- FUNCTION --------------------------------------*/
public:
	FORCEINLINE DECLARE_GETTER_SETTER(From, m_from, int32);
	FORCEINLINE DECLARE_GETTER_SETTER(To, m_to, int32);
	FORCEINLINE DECLARE_GETTER_SETTER(Cost, m_cost, float);

	/*
	* @outer : who hold the new edges
	*/
	static UCPathEdge* GetNewEdges(UObject* Outer);

	/* ---------------------------------- OVERRIDE --------------------------------------*/
};
