#include "DofHandler.h"

void DofHandler::PrintDofMap()const {
    cout<<"*** Summary of dof maps:"<<endl;
    printf("*** nDofs=%6d, nDofsPerNode=%2d, nDofsPerElmt=%2d\n",_nDofs,_nDofsPerNode,_nDofsPerElmt);
    for(int e=1;e<=_nElmts;++e){
        printf("*** %5d-th elmt:",e);
        for(int i=1;i<=_nDofsPerElmt;++i){
            printf("%5d ",GetIthElmtJthDofIndex(e,i));
        }
        cout<<endl;
    }
}