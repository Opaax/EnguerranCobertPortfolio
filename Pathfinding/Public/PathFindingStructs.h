#pragma once

#include "CoreMinimal.h"
#include "PathFindingStructs.generated.h"

class UCPathEdge;
class UWorld;

/*
 * Contains All egdes for a node
 */
USTRUCT(BlueprintType, Blueprintable, meta = (HasNativeMake = "VampiresTD.CBPFunctionLibraryStruct.MakeEdgesHandle", HasNativeBreak = "VampiresTD.CBPFunctionLibraryStruct.BreakEdgesHandle"))
struct VAMPIRESTD_API FEdgesHandle
{
	GENERATED_BODY()

	/* ---------------------------------- MEMBERS --------------------------------------*/
public:
	TArray<UCPathEdge*> AllEdges;

	/* ---------------------------------- FUNCTIONS --------------------------------------*/
	//CTOR
	FEdgesHandle() : AllEdges() { }
	FEdgesHandle(const TArray<UCPathEdge*>& Edges) : AllEdges(Edges) { }
};

/*
 * Contain a Path
 */
USTRUCT(BlueprintType, Blueprintable, meta = (HasNativeMake = "VampiresTD.CBPFunctionLibraryStruct.MakePathHandle", HasNativeBreak = "VampiresTD.CBPFunctionLibraryStruct.BreakPathHandle"))
struct VAMPIRESTD_API FPathHandle
{
	GENERATED_BODY()

		/* ---------------------------------- MEMBERS --------------------------------------*/
public:
	TArray<int32> Path;

	/* ---------------------------------- FUNCTIONS --------------------------------------*/
	//CTOR
	FPathHandle() : Path(){ }
	FPathHandle(const TArray<int32>& InPath) : Path(InPath) { }
};