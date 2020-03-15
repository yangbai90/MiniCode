#pragma once

#include "Mesh.h"
#include "petsc.h"

void LocalElmt(const int &e,const int &n){
    double sum;
    sum=0.0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            sum+=sin(1.0*i)*cos(1.0*j)*e;
        }
    }
    sum=sqrt(sum);
}

void NormFEMAssemble(const Mesh &mesh,Mat &A,Vec &rhs){

    PetscMPIInt rank,size;
    int rankne,eStart,eEnd;
    int ei,e,i,j,iInd,jInd;
    VecSet(rhs,0.0);
    MatScale(A,0.0);
    
    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    rankne=mesh.GetElmtsNum()/size;
    eStart=rank*rankne;
    eEnd=eStart+rankne;
    if(rank==size-1) eEnd=mesh.GetElmtsNum();


    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"We start to assemble the sparse matrix ...\n");
    for(ei=eStart;ei<eEnd;++ei){
        e=ei+1;
        LocalElmt(e,9);
        for(i=1;i<=9;++i){
            iInd=mesh.GetIthElmtJthIndex(e,i)-1;
            VecSetValue(rhs,iInd,1.0,ADD_VALUES);
            for(j=1;j<=9;++j){
                jInd=mesh.GetIthElmtJthIndex(e,j)-1;
                MatSetValue(A,iInd,jInd,1.0,ADD_VALUES);
            }
        }       
    }
    MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
    VecAssemblyBegin(rhs);
    VecAssemblyEnd(rhs);
}