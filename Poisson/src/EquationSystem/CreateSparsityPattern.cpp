#include "EquationSystem.h"

void EquationSystem::CreateSparsityPattern(DofHandler &dofHandler){
    int e,i,j,ii,jj,iInd,jInd;
    int nDofsPerNode;
    nDofsPerNode=dofHandler.GetDofsNumPerNode();
    vector<int> elDofs;
    elDofs.resize(dofHandler.GetDofsNumPerElmt(),0);
    _ZeroCoeffs.clear();
    int nDofsPerElmt=dofHandler.GetDofsNumPerElmt();
    for(e=1;e<=dofHandler.GetElmtsNum();++e){
        dofHandler.GetIthElmtDofIndex(e,elDofs);
        for(i=0;i<nDofsPerElmt;++i){
            iInd=elDofs[i]-1;
            for(j=0;j<nDofsPerElmt;++j){
                jInd=elDofs[j]-1;
                _ZeroCoeffs.push_back(T(iInd,jInd,0.0));
            }
        }
    }
    _AMATRIX.setFromTriplets(_ZeroCoeffs.begin(),_ZeroCoeffs.end());
    _AMATRIX.finalize();
}