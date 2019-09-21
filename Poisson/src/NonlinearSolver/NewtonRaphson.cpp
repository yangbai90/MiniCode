#include "NonlinearSolver.h"

bool NonlinearSolver::NewtonRaphson(Mesh &mesh,DofHandler &dofHandler,SolutionSystem &solutionSystem,EquationSystem &equationSystem,FESystem &feSystem){
    int iters=0;
    bool IsConvergent=false;

    while(iters<_MaxIters && !IsConvergent){
        feSystem.FormKR(6,mesh,dofHandler,solutionSystem._U,solutionSystem._V,equationSystem._AMATRIX,equationSystem._RHS);
        if(!Solve(equationSystem._AMATRIX,equationSystem._dU,equationSystem._RHS)){
            cout<<"*** Error: solve Ax=F failed in NR iteration, iters="<<iters+1<<endl;
            return false;
        }
        _Rnorm=equationSystem._RHS.norm();
        _Enorm=equationSystem._dU.norm()*_Rnorm;
        if(iters==0){
            _Rnorm0=_Rnorm;
            _Enorm0=_Enorm;
        }

        // update
        iters+=1;
        if(CheckConvergence()){
            IsConvergent=true;
            break;
        }
        printf("*** Iters=%2d, |R|=%12.5e, |E|=%12.5e\n",iters,_Rnorm,_Enorm);
    }
}