#include <iostream>

#include "Welcome.h"

#include "Mesh.h"
#include "DofHandler.h"

using namespace std;


int main()
{
    Welcome();

    Mesh mesh;
    mesh.CreateMesh(10,0.0,1.0,"edge4");
    mesh.PrintMeshInfo();

    DofHandler dofHandler;
    dofHandler.CreateDofMap(2,mesh);
    dofHandler.PrintDofMap();
    return 0;
}
