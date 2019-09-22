#include "NonlinearSolver.h"

bool NonlinearSolver::NewtonRaphson(Mesh &mesh,DofHandler &dofHandler,SolutionSystem &solutionSystem,EquationSystem &equationSystem,FESystem &feSystem){
    int Iters=0;
    bool IsConvergent=false;
    solutionSystem._U*=0.0;
    feSystem.PresetDirichletBC(dofHandler,solutionSystem._U);
    _Rnorm=1.0;_Enorm=1.0;
    while(Iters<_MaxIters && !IsConvergent){
        feSystem.FormKR(6,mesh,dofHandler,solutionSystem._U,solutionSystem._V,equationSystem._AMATRIX,equationSystem._RHS);
        feSystem.ApplyBC(dofHandler,equationSystem._AMATRIX,equationSystem._RHS,solutionSystem._U);
        if(!Solve(equationSystem._AMATRIX,equationSystem._dU,equationSystem._RHS)){
            cout<<"*** Error: solve Ax=F failed in NR iteration, iters="<<Iters+1<<endl;
            return false;
        }
        _Rnorm=equationSystem._RHS.norm();
        _Enorm=equationSystem._dU.norm()*_Rnorm;
        if(Iters==0){
            _Rnorm0=_Rnorm;
            _Enorm0=_Enorm;
        }

        // update
        Iters+=1;
        solutionSystem._U+=equationSystem._dU;

        // printf("*** Iters=%2d, Maxiter=%d, |R|=%12.5e, |E|=%12.5e\n",Iters,_MaxIters,_Rnorm,_Enorm);

        if(CheckConvergence()){
            // cout<<"works"<<endl;
            IsConvergent=true;
            break;
        }
        // if(iters>_MaxIters) {
        //     cout<<"works"<<endl;
        //     break;
        // }
        
    }
    if(IsConvergent){
        cout<<"*** Newton-Raphson iteration finished! solution convergent"<<endl;
        // printf("*** Iters=%2d, Maxiter=%d, |R|=%12.5e, |E|=%12.5e\n",Iters,_MaxIters,_Rnorm,_Enorm);
        // cout<<"*** Iters="<<Iters
        //     <<", Maxiter="<<_MaxIters
        //     <<", |R|="<<_Rnorm<<endl;
        return IsConvergent;
    }
    else{
        cout<<"*** Error: Newton-Raphson failed! Can\'t have convergence solution!!!"<<endl;
        return false;
    }
}