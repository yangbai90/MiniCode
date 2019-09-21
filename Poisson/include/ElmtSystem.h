#ifndef ELMTSYSTEM_H
#define ELMTSYSTEM_H

#include <iostream>
#include <vector>

#include "Eigen/Eigen"

#include "ShapeFun.h"
#include "QPoint.h"

using namespace std;

class ElmtSystem
{
public:
    void ElmtLib(const int &isw,
                 const vector<double> &U,const vector<double> &V,const vector<double> &Coords,
                 ShapeFun &shp,QPoint qpoint,
                 Eigen::MatrixXd &K,Eigen::VectorXd &rhs);
    
private:
    void Poisson(const int &isw,
                 const vector<double> &U,const vector<double> &V,const vector<double> &Coords,
                 ShapeFun &shp,QPoint qpoint,
                 Eigen::MatrixXd &K,Eigen::VectorXd &rhs);

};

#endif // ELMTSYSTEM_H