#ifndef FESYSTEM_H
#define FESYSTEM_H

#include <iostream>
#include <string>

#include "Mesh.h"
#include "DofHandler.h"


#include "Eigen/Eigen"

using namespace std;

class FESystem
{
public:
    FESystem();


    void FormKR(const int &isw,Mesh &mesh,DofHandler &dofHandler,const Eigen::VectorXd &U,const Eigen::VectorXd &V,
                Eigen::SparseMatrix<double> &AMATRIX,Eigen::VectorXd &RHS);
    

private:

};

#endif // FESYSTEM_H