#include "FESystem.h"

void FESystem::Init(Mesh &mesh){
    shp.SetDim(1);
    shp.SetShapeFunNum(mesh.GetNodesNumPerElmt());
    shp.PreCalc();

    qpoint.SetDim(1);
    qpoint.SetQPointOrder(4);
    qpoint.CreateQPoints();
}