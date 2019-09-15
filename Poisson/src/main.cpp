#include <iostream>

#include "Welcome.h"
#include "Mesh.h"

using namespace std;


int main()
{
    Welcome();

    Mesh mesh;
    mesh.CreateMesh(1000,0.0,1.0,"edge4");
    mesh.PrintMeshInfo();
    return 0;
}
