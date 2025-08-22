#include "Utils/TDAlgo.h"
#include "PathFinding/CPathFindingNode.h"

bool FPFNodeTopLeftToBottomRight::operator()(const UCPathFindingNode& A, const UCPathFindingNode& B) const
{
    if (IsValid(&A) && IsValid(&B))
    {
        FVector lLocA = A.GetNodeLocation();
        FVector lLocB = B.GetNodeLocation();

        //If X are same check Y
        //Low Y goes to left Big Y goes to Right
        if (lLocB.X == lLocA.X) {
            return lLocB.Y > lLocA.Y;
        }

        //Big X goes to Top Low X goes to Bottom
        return lLocA.X > lLocB.X;
    }
    return false;
}
