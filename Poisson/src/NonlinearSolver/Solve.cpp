#include "NonlinearSolver.h"

bool NonlinearSolver::Solve(Eigen::SparseMatrix<double> &A,Eigen::VectorXd &x,Eigen::VectorXd &F){
    _solver.compute(A);
    if(_solver.info()!=Eigen::Success){
        cout<<"*** Error: decomposition failed!"<<endl;
        return false;
    }
    x=_solver.solve(F);
    if(_solver.info()!=Eigen::Success){
        cout<<"*** Error: SparseLU solve failed!"<<endl;
        return false;
    }
    return true;
}