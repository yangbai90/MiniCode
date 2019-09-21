#include "NonlinearSolver.h"

bool NonlinearSolver::NonLinearSolve(Mesh &mesh,DofHandler &dofHandler,SolutionSystem &solutionSystem,EquationSystem &equationSystem,FESystem &feSystem){
    if(_Method==NonLinearMethod::NEWTONRAPHSON){
        return NewtonRaphson(mesh,dofHandler,solutionSystem,equationSystem,feSystem);
    }
}