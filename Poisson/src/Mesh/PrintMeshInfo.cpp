#include "Mesh.h"

void Mesh::PrintMeshInfo() const{
    cout<<"*** Summary of mesh information:"<<endl;
    cout<<"*** nElmts="<<_nElmts<<", nNodes="<<_nNodes<<", nNodesPerElmt="<<_nNodesPerElmt<<endl;
    for(int i=1;i<=_nNodes;++i){
        printf("*** %6d-th node:",i);
        for(int j=1;j<=3;++j){
            printf("%12.5f ",GetIthNodeJthCoord(i,j));
        }
        cout<<endl;
    }
    for(int e=1;e<=_nElmts;++e){
        printf("*** %6d-th elmt:",e);
        for(int j=1;j<=_nNodesPerElmt;j++){
            printf("%6d ",GetIthElmtJthNodeIndex(e,j));
        }
        cout<<endl;
    }
}