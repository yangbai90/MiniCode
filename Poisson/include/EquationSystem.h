#ifndef EQUATIONSYSTEM_H
#define EQUATIONSYSTEM_H

#include <iostream>
#include <vector>
#include <cmath>

#include "Eigen/Eigen"

#include "DofHandler.h"

using namespace std;

typedef Eigen::Triplet<double> T;

class EquationSystem
{
public:
    EquationSystem();

    void InitEquationSystem(const int &ndofs);
    void CreateSparsityPattern(DofHandler &dofHandler);

public:
    // equation matrix for the system
    Eigen::SparseMatrix<double> _AMATRIX;
    Eigen::VectorXd _RHS,_dU;

    vector<T> _ZeroCoeffs;

private:
    int _nDofs;
};


#endif // EQUATIONSYSTEM_H