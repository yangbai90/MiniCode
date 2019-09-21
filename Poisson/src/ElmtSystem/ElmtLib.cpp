#include "ElmtSystem.h"

void ElmtSystem::ElmtLib(const int &isw,
                 const vector<double> &U,const vector<double> &V,const vector<double> &Coords,
                 ShapeFun &shp,QPoint qpoint,
                 Eigen::MatrixXd &K,Eigen::VectorXd &rhs){
    Poisson(isw,U,V,Coords,shp,qpoint,K,rhs);
}