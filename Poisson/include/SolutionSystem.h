#ifndef SOLUTIONSYSTEM_H
#define SOLUTIONSYSTEM_H

#include <iostream>
#include <vector>


#include "Eigen/Eigen"

using namespace std;

class SolutionSystem
{
public:
    SolutionSystem();

    void Init(const int &ndofs);

public:
    Eigen::VectorXd _U,_Uold;
    Eigen::VectorXd _V,_Vold;
private:
    int _nDofs;
};

#endif // SOLUTIONSYSTEM_H