#ifndef NONLINEARSOLVER_H
#define NONLINEARSOLVER_H

#include <iostream>
#include <iomanip>

#include "Eigen/Eigen"


#include "DofHandler.h"
#include "EquationSystem.h"
#include "Mesh.h"
#include "SolutionSystem.h"
#include "FESystem.h"

using namespace std;

enum class NonLinearMethod
{
    NEWTONRAPHSON,
    NEWTONRAPHSONWITHLINESEARCH,
    NEWTONRAPHSONMODIFY
};

class NonlinearSolver
{
public:
    NonlinearSolver();
    
    void SetMaxIters(const int &iters) {_MaxIters=iters;}
    void SetResidualRelTol(const double &tol) {_Rrtol=tol;}
    void SetResidualAbsTol(const double &tol) {_Ratol=tol;}
    void SetEnergyRelTol(const double &tol) {_Ertol=tol;}
    void SetEnergyAbsTol(const double &tol) {_Eatol=tol;}
    void SetConvergenceCriterion(const int &choice){_Criterion=choice;}

    bool NonLinearSolve(Mesh &mesh,DofHandler &dofHandler,SolutionSystem &solutionSystem,EquationSystem &equationSystem,FESystem &feSystem);
    bool Solve(Eigen::SparseMatrix<double> &A,Eigen::VectorXd &x,Eigen::VectorXd &F);


private:
    bool NewtonRaphson(Mesh &mesh,DofHandler &dofHandler,SolutionSystem &solutionSystem,EquationSystem &equationSystem,FESystem &feSystem);
    
    bool CheckConvergence();

private:
    NonLinearMethod _Method;
    int _MaxIters,_Criterion;
    double _Rrtol,_Ratol,_Ertol,_Eatol;
    double _Rnorm0,_Rnorm,_Enorm0,_Enorm;

    Eigen::SparseLU<Eigen::SparseMatrix<double>> _solver;
};

#endif // NONLINEARSOLVER_H