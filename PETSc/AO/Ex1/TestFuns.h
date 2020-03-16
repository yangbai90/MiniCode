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
    int ei,e,i,j,iInd,jInd,gp;
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
        for(gp=1;gp<=9;gp++){
            LocalElmt(e, 9);
            for (i = 1; i <= 9; ++i)
            {
                iInd = mesh.GetIthElmtJthIndex(e, i) - 1;
                VecSetValue(rhs, iInd, 1.0, ADD_VALUES);
                for (j = 1; j <= 9; ++j)
                {
                    jInd = mesh.GetIthElmtJthIndex(e, j) - 1;
                    MatSetValue(A, iInd, jInd, 1.0, ADD_VALUES);
                }
            }
        }       
    }
    MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
    VecAssemblyBegin(rhs);
    VecAssemblyEnd(rhs);
}

//*****************************************************
void ScatterFEMAssemble(const Mesh &mesh,const Vec &U,Mat &A,Vec &rhs){

    VecScatter scatteru;
    Vec Useq;
    PetscMPIInt rank,size;
    int rankne,eStart,eEnd;
    int ei,e,i,j,iInd,jInd,gp;
    VecSet(rhs,0.0);
    MatScale(A,0.0);
    double vals;
    
    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    VecScatterCreateToAll(U,&scatteru,&Useq);
    VecScatterBegin(scatteru,U,Useq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatteru,U,Useq,INSERT_VALUES,SCATTER_FORWARD);

    rankne=mesh.GetElmtsNum()/size;
    eStart=rank*rankne;
    eEnd=eStart+rankne;
    if(rank==size-1) eEnd=mesh.GetElmtsNum();


    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"We start to assemble the sparse matrix ...\n");
    for(ei=eStart;ei<eEnd;++ei){
        e=ei+1;
        for(gp=1;gp<=9;gp++){
            LocalElmt(e, 9);
            for (i = 1; i <= 9; ++i)
            {
                iInd = mesh.GetIthElmtJthIndex(e, i) - 1;
                VecGetValues(Useq, 1, &iInd, &vals);
                VecSetValue(rhs, iInd, vals, ADD_VALUES);
                for (j = 1; j <= 9; ++j)
                {
                    jInd = mesh.GetIthElmtJthIndex(e, j) - 1;
                    MatSetValue(A, iInd, jInd, vals, ADD_VALUES);
                }
            }
        }      
    }
    MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
    VecAssemblyBegin(rhs);
    VecAssemblyEnd(rhs);

    VecScatterDestroy(&scatteru);
    VecDestroy(&Useq);
}

//*****************************************************
void Scatter1FEMAssemble(const Mesh &mesh,const Vec &U,const Vec &V,Mat &A,Vec &rhs){

    VecScatter scatteru,scatterv;
    Vec Useq,Vseq;
    PetscMPIInt rank,size;
    int rankne,eStart,eEnd;
    int ei,e,i,j,iInd,jInd,gp;
    VecSet(rhs,0.0);
    MatScale(A,0.0);
    double vals;
    
    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    VecScatterCreateToAll(U,&scatteru,&Useq);
    VecScatterBegin(scatteru,U,Useq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatteru,U,Useq,INSERT_VALUES,SCATTER_FORWARD);

    VecScatterCreateToAll(V,&scatterv,&Vseq);
    VecScatterBegin(scatterv,V,Vseq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatterv,V,Vseq,INSERT_VALUES,SCATTER_FORWARD);

    rankne=mesh.GetElmtsNum()/size;
    eStart=rank*rankne;
    eEnd=eStart+rankne;
    if(rank==size-1) eEnd=mesh.GetElmtsNum();


    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"We start to assemble the sparse matrix ...\n");
    for(ei=eStart;ei<eEnd;++ei){
        e=ei+1;
        for(gp=1;gp<=9;gp++){
            LocalElmt(e, 9);
            for (i = 1; i <= 9; ++i)
            {
                iInd = mesh.GetIthElmtJthIndex(e, i) - 1;
                VecGetValues(Useq, 1, &iInd, &vals);
                VecSetValue(rhs, iInd, vals, ADD_VALUES);
                for (j = 1; j <= 9; ++j)
                {
                    VecGetValues(Vseq, 1, &iInd, &vals);
                    jInd = mesh.GetIthElmtJthIndex(e, j) - 1;
                    MatSetValue(A, iInd, jInd, vals, ADD_VALUES);
                }
            }
        }      
    }
    MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
    VecAssemblyBegin(rhs);
    VecAssemblyEnd(rhs);

    VecScatterDestroy(&scatteru);
    VecDestroy(&Useq);
    VecScatterDestroy(&scatterv);
    VecDestroy(&Vseq);
}

//*****************************************************
void Scatter2FEMAssemble(const Mesh &mesh,const Vec &U,const Vec &V,const Vec &Proj,const Vec &Hist,Mat &A,Vec &rhs){

    VecScatter scatteru,scatterv,scatterproj,scatterhist;
    Vec Useq,Vseq;
    Vec Projseq,Histseq;
    PetscMPIInt rank,size;
    int rankne,eStart,eEnd;
    int ei,e,i,j,iInd,jInd,ii,gp;
    VecSet(rhs,0.0);
    MatScale(A,0.0);
    double vals;
    
    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    VecScatterCreateToAll(U,&scatteru,&Useq);
    VecScatterBegin(scatteru,U,Useq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatteru,U,Useq,INSERT_VALUES,SCATTER_FORWARD);

    VecScatterCreateToAll(V,&scatterv,&Vseq);
    VecScatterBegin(scatterv,V,Vseq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatterv,V,Vseq,INSERT_VALUES,SCATTER_FORWARD);

    VecScatterCreateToAll(Proj,&scatterproj,&Projseq);
    VecScatterBegin(scatterproj,Proj,Projseq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatterproj,Proj,Projseq,INSERT_VALUES,SCATTER_FORWARD);

    VecScatterCreateToAll(Hist,&scatterhist,&Histseq);
    VecScatterBegin(scatterhist,Hist,Histseq,INSERT_VALUES,SCATTER_FORWARD);
    VecScatterEnd(scatterhist,Hist,Histseq,INSERT_VALUES,SCATTER_FORWARD);


    rankne=mesh.GetElmtsNum()/size;
    eStart=rank*rankne;
    eEnd=eStart+rankne;
    if(rank==size-1) eEnd=mesh.GetElmtsNum();


    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"We start to assemble the sparse matrix ...\n");
    for(ei=eStart;ei<eEnd;++ei){
        e=ei+1;
        LocalElmt(e,9);
        for(gp=0;gp<9;gp++){
            for (i = 1; i <= 9; ++i){
                iInd = mesh.GetIthElmtJthIndex(e, i) - 1;
                VecGetValues(Useq, 1, &iInd, &vals);
                ii=iInd*9+gp-1;
                VecGetValues(Histseq,1,&ii,&vals);
                VecGetValues(Projseq,1,&ii,&vals);
                VecSetValue(rhs, iInd, vals, ADD_VALUES);
                for (j = 1; j <= 9; ++j){
                    VecGetValues(Vseq, 1, &iInd, &vals);
                    jInd = mesh.GetIthElmtJthIndex(e, j) - 1;
                    MatSetValue(A, iInd, jInd, vals, ADD_VALUES);
                }
            }
        }   
    }
    MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
    VecAssemblyBegin(rhs);
    VecAssemblyEnd(rhs);

    VecScatterDestroy(&scatteru);
    VecDestroy(&Useq);
    VecScatterDestroy(&scatterv);
    VecDestroy(&Vseq);
}