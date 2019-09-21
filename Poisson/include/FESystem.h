#ifndef FESYSTEM_H
#define FESYSTEM_H

#include <iostream>
#include <string>

#include "Mesh.h"
#include "DofHandler.h"

#include "ElmtSystem.h"
#include "ShapeFun.h"
#include "QPoint.h"

#include "Eigen/Eigen"

using namespace std;

class FESystem
{
public:
    // FESystem();
    void Init(Mesh &mesh);


    void FormKR(const int &isw,Mesh &mesh,DofHandler &dofHandler,const Eigen::VectorXd &U,const Eigen::VectorXd &V,
                Eigen::SparseMatrix<double> &AMATRIX,Eigen::VectorXd &RHS);
    
private:
    ElmtSystem elmtSystem;
    ShapeFun shp;
    QPoint qpoint;

};

#endif // FESYSTEM_H