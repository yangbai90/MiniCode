#include <iostream>

#include "Welcome.h"

#include "Mesh.h"
#include "DofHandler.h"
#include "EquationSystem.h"
#include "FESystem.h"
#include "SolutionSystem.h"
#include "NonlinearSolver.h"

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

    EquationSystem equationSystem;
    equationSystem.InitEquationSystem(dofHandler.GetDofsNum());
    equationSystem.CreateSparsityPattern(dofHandler);

    FESystem feSystem;
    feSystem.Init(mesh);

    SolutionSystem solutionSystem;
    solutionSystem.Init(dofHandler.GetDofsNum());

    NonlinearSolver nonlinearSolver;
    nonlinearSolver.NonLinearSolve(mesh,dofHandler,solutionSystem,equationSystem,feSystem);
    
    
    return 0;
}
