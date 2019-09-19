#include "DofHandler.h"

void DofHandler::CreateDofMap(int ndofspernode,Mesh &mesh){
    _nNodes=mesh.GetNodesNum();
    _nElmts=mesh.GetElmtsNum();
    _nDofsPerNode=ndofspernode;
    _nDofsPerElmt=ndofspernode*mesh.GetNodesNumPerElmt();
    _nNodesPerElmt=mesh.GetNodesNumPerElmt();
    _nDofs=_nNodes*_nDofsPerNode;

    _NodalDofMap.reserve(_nDofs);
    int e,i,j,k,iInd;
    k=0;
    for(i=1;i<=_nNodes;++i){
        for(j=1;j<=_nDofsPerNode;++j){
            k+=1;
            _NodalDofMap.push_back(k);
        }
    }

    _ElmtDofMap.reserve(_nElmts*_nDofsPerElmt);
    for(e=1;e<=_nElmts;++e){
        for(i=1;i<=_nNodesPerElmt;++i){
            iInd=mesh.GetIthElmtJthNodeIndex(e,i);
            for(k=1;k<=_nDofsPerNode;++k){
                _ElmtDofMap.push_back(_NodalDofMap[(iInd-1)*_nDofsPerNode+k-1]);
            }
        }
    }
}