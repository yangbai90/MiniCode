#ifndef BCSYSTEM_H
#define BCSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "DofHandler.h"

#include "Eigen/Eigen"

using namespace std;


class BCSystem
{
public:
    BCSystem();
    void SetBC(string sidename,string bctype,double bcvalue);

    void PresetDirichlet(DofHandler &dofHandler,Eigen::VectorXd &U);
    void ApplyBC(DofHandler &dofHandler,Eigen::SparseMatrix<double> &K,Eigen::VectorXd &RHS,Eigen::VectorXd &U);

    void PrintBCInfo() const;
private:
    vector<pair<string,string>> _BCInfo;
    vector<double> _BCValue;
};



#endif // BCSYSTEM_H