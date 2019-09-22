#ifndef FESYSTEM_H
#define FESYSTEM_H

#include <iostream>
#include <string>

#include "Mesh.h"
#include "DofHandler.h"

#include "ElmtSystem.h"
#include "ShapeFun.h"
#include "QPoint.h"
#include "BCSystem.h"

#include "Eigen/Eigen"

using namespace std;

class FESystem
{
public:
    FESystem(){IsInit=true;}
    void Init(Mesh &mesh);
    void SetBC(string side,string type,double bcvalue){bcSystem.SetBC(side,type,bcvalue);}
    void PresetDirichletBC(DofHandler &dofHandler,Eigen::VectorXd &U){
        bcSystem.PresetDirichlet(dofHandler,U);
    }
    void ApplyBC(DofHandler &dofHandler,Eigen::SparseMatrix<double> &K,Eigen::VectorXd &RHS,Eigen::VectorXd &U){
        bcSystem.ApplyBC(dofHandler,K,RHS,U);
    }
    void FormKR(const int &isw,Mesh &mesh,DofHandler &dofHandler,const Eigen::VectorXd &U,const Eigen::VectorXd &V,
                Eigen::SparseMatrix<double> &AMATRIX,Eigen::VectorXd &RHS);

    void PrintBCInfo() const{bcSystem.PrintBCInfo();}
    
private:
    bool IsInit=false;
    ElmtSystem elmtSystem;
    BCSystem bcSystem;
    ShapeFun shp;
    QPoint qpoint;

};

#endif // FESYSTEM_H