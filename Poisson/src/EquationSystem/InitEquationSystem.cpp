#include "EquationSystem.h"

void EquationSystem::InitEquationSystem(const int &ndofs){
    _nDofs=ndofs;
    _AMATRIX=Eigen::SparseMatrix<double>(_nDofs,_nDofs);

    _RHS=Eigen::VectorXd::Zero(_nDofs);
    _dU=Eigen::VectorXd::Zero(_nDofs);
}