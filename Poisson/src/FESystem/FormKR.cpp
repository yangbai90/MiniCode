#include "FESystem.h"

void FESystem::FormKR(const int &isw,
                      Mesh &mesh,DofHandler &dofHandler,
                      const Eigen::VectorXd &U,const Eigen::VectorXd &V,
                      Eigen::SparseMatrix<double> &AMATRIX,Eigen::VectorXd &RHS){
    AMATRIX*=0.0;
    RHS*=0.0;
    vector<int> elConn,elDofs;
    int e,i,j;
    int nNodesPerElmt=mesh.GetNodesNumPerElmt();
    int nDofsPerElmt=dofHandler.GetDofsNumPerElmt();
    elConn.resize(nNodesPerElmt,0);
    elDofs.resize(nDofsPerElmt,0);
    vector<double> elU,elV,elCoords;
    elU.resize(nDofsPerElmt,0.0);
    elV.resize(nDofsPerElmt,0.0);
    elCoords.resize(nNodesPerElmt,0.0);
    Eigen::MatrixXd localK(nDofsPerElmt,nDofsPerElmt);
    Eigen::VectorXd localR(nDofsPerElmt);
    for(e=1;e<=mesh.GetElmtsNum();++e){
        mesh.GetIthElmtNodeIndex(e,elConn);
        mesh.GetIthElmtNodeCoords(e,elCoords);
        dofHandler.GetIthElmtDofIndex(e,elDofs);
        for(i=0;i<nDofsPerElmt;i++){
            elU[i]=U(elDofs[i]-1);
            elV[i]=V(elDofs[i]-1);
        }
        elmtSystem.ElmtLib(isw,elU,elV,elCoords,shp,qpoint,localK,localR);
        if(isw==3||isw==6){
            for(i=0;i<nDofsPerElmt;++i){
                RHS(elDofs[i]-1)+=localR(i);
                if(isw==6){
                    for(j=0;j<nDofsPerElmt;++j){
                        AMATRIX.coeffRef(elDofs[i]-1,elDofs[j]-1)+=localK(i,j);
                    }
                }
            }
        }
    }
}