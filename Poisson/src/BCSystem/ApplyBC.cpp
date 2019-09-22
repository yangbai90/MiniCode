#include "BCSystem.h"

void BCSystem::PresetDirichlet(DofHandler &dofHandler,Eigen::VectorXd &U){
    int nDofs=dofHandler.GetDofsNum();
    int iInd;
    iInd=0;
    for(unsigned ibc=0;ibc<_BCInfo.size();++ibc){
        if(_BCInfo[ibc].second=="dirichlet"){
            if(_BCInfo[ibc].first=="left"){
                iInd=0;
            }
            else if(_BCInfo[ibc].first=="right"){
                iInd=nDofs-1;
            }
            U(iInd)=_BCValue[ibc];
        }
        else {
            continue;
        }
    }
}
//**********************************************************
void BCSystem::ApplyBC(DofHandler &dofHandler,Eigen::SparseMatrix<double> &K,Eigen::VectorXd &RHS,Eigen::VectorXd &U){
    int nDofs=dofHandler.GetDofsNum();
    int iInd=0;
    for(unsigned ibc=0;ibc<_BCInfo.size();++ibc){
        if(_BCInfo[ibc].second=="dirichlet"){
            if(_BCInfo[ibc].first=="left"){
                iInd=0;
            }
            else if(_BCInfo[ibc].first=="right"){
                iInd=nDofs-1;
            }
            U(iInd)=_BCValue[ibc];
            K.coeffRef(iInd,iInd)=1.0e16;
            RHS(iInd)=0.0;
        }
        else if(_BCInfo[ibc].second=="neumann"){
            if(_BCInfo[ibc].first=="left"){
                iInd=0;
            }
            else if(_BCInfo[ibc].first=="right"){
                iInd=nDofs-1;
            }
            RHS(iInd)+=_BCValue[ibc];
        }
    }
}