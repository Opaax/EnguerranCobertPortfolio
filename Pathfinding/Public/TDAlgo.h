#pragma once

#include "CoreMinimal.h"
//#include "TDAlgo.generated.h"

class UCPathFindingNode;

struct FPFNodeTopLeftToBottomRight
{
    bool operator()(const UCPathFindingNode& A, const UCPathFindingNode& B) const;
};
