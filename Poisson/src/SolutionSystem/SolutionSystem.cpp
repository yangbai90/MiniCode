#include "SolutionSystem.h"

SolutionSystem::SolutionSystem(){
    _nDofs=0;
}
//************************
void SolutionSystem::Init(const int &ndofs){
    _nDofs=ndofs;
    _U=Eigen::VectorXd(_nDofs);
    _Uold=Eigen::VectorXd(_nDofs);
    _V=Eigen::VectorXd(_nDofs);
    _Vold=Eigen::VectorXd(_nDofs);
}