#include "ElmtSystem.h"

void ElmtSystem::Poisson(const int &isw,
                 const vector<double> &U,const vector<double> &V,const vector<double> &Coords,
                 ShapeFun &shp,QPoint qpoint,
                 Eigen::MatrixXd &K,Eigen::VectorXd &rhs){
    if(isw==3||isw==6){
        rhs*=0.0;
        if(isw==6){
            K*=0.0;
        }
    }
    double xi,w,detjac,JxW,gpInd;
    double gradPhi,phi;
    double sigma=1.0;
    double F=2.0;
    int nNodes=int(Coords.size());
    int i,j;
    for(gpInd=1;gpInd<=qpoint.GetQpPointsNum();gpInd++){
        xi=qpoint(gpInd,1);
        w=qpoint(gpInd,0);
        shp.Calc(xi,Coords);
        JxW=w*shp.GetDetJac();
        gradPhi=0.0;phi=0.0;
        for(i=1;i<=nNodes;++i){
            gradPhi+=shp(i,1)*U[i-1];
            phi+=shp(i,0)*U[i-1];
        }
        if(isw==3||isw==6)
        for(i=1;i<=nNodes;++i){
            // for residual
            rhs(i-1)+=sigma*gradPhi*shp(i,1)*JxW+F*shp(i,0)*JxW;
            //
            if(isw==6){
                for(j=1;j<=nNodes;++j){
                    K.coeffRef(i-1,j-1)+=-sigma*shp(j,1)*shp(i,1)*JxW;
                }
            }
        }
    }
}