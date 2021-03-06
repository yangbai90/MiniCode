#include <iostream>
#include <chrono>
#include <cmath>
#include "petsc.h"

#include "Mesh.h"

#include "TestFuns.h"

using namespace std;



int main(int args,char *argv[]){
    chrono::high_resolution_clock::time_point starttime,endtime;
    PetscErrorCode ierr;
    Mat A;
    Vec rhs;
    Vec U,V;
    Vec Proj,Hist;
    // AO ao;
    PetscMPIInt rank,size;
    int ne=500;

    int rankne;
    int eStart,eEnd;
    int ei,e,i,j;
    int iInd,jInd;


    ierr=PetscInitialize(&args,&argv,NULL,NULL);

    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    PetscOptionsGetInt(NULL,NULL,"-ne",&ne,NULL);

    Mesh mesh(ne,ne);

    mesh.CreateMesh();

    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"*** Number of nodes=%8d, number of elmts=%8d\n",mesh.GetNodesNum(),mesh.GetElmtsNum());


   
    MatCreateAIJ(PETSC_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,mesh.GetNodesNum(),mesh.GetNodesNum(),4*9,NULL,4*9,NULL,&A);
    MatSetFromOptions(A);
    MatSetUp(A);

    VecCreate(PETSC_COMM_WORLD,&rhs);
    VecSetSizes(rhs,PETSC_DECIDE,mesh.GetNodesNum());
    VecSetFromOptions(rhs);
    VecSetUp(rhs);

    VecCreate(PETSC_COMM_WORLD,&U);
    VecSetSizes(U,PETSC_DECIDE,mesh.GetNodesNum());
    VecSetFromOptions(U);
    VecSetUp(U);

    VecCreate(PETSC_COMM_WORLD,&V);
    VecSetSizes(V,PETSC_DECIDE,mesh.GetNodesNum());
    VecSetFromOptions(V);
    VecSetUp(V);


    VecCreate(PETSC_COMM_WORLD,&Proj);
    VecSetSizes(Proj,PETSC_DECIDE,mesh.GetNodesNum()*12);
    VecSetFromOptions(Proj);
    VecSetUp(Proj);

    VecCreate(PETSC_COMM_WORLD,&Hist);
    VecSetSizes(Hist,PETSC_DECIDE,mesh.GetNodesNum()*9);
    VecSetFromOptions(Hist);
    VecSetUp(Hist);



    int i1,i2;
    VecGetOwnershipRange(U,&i1,&i2);
    for(i=i1;i<i2;++i){
        VecSetValue(U,i,sin(1.0*i),INSERT_VALUES);
        VecSetValue(V,i,cos(1.0*i),INSERT_VALUES);
    }
    VecAssemblyBegin(U);
    VecAssemblyEnd(U);
    VecAssemblyBegin(V);
    VecAssemblyEnd(V);

    if(rank==0){
        starttime=chrono::high_resolution_clock::now();
    }


    rankne=mesh.GetElmtsNum()/size;
    eStart=rank*rankne;
    eEnd=eStart+rankne;
    if(rank==size-1) eEnd=mesh.GetElmtsNum();
    

    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"number of cpus=%3d, each process has %6d elmts\n",size,rankne);

    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"We start to initialize the sparse matrix ...\n");
    for(ei=eStart;ei<eEnd;++ei){
        e=ei+1;
        LocalElmt(e,9);
        for(i=1;i<=9;++i){
            iInd=mesh.GetIthElmtJthIndex(e,i)-1;
            VecSetValue(rhs,iInd,1.0,INSERT_VALUES);
            for(j=1;j<=9;++j){
                jInd=mesh.GetIthElmtJthIndex(e,j)-1;
                MatSetValue(A,iInd,jInd,1.0,INSERT_VALUES);
            }
        }       
    }
    MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
    VecAssemblyBegin(rhs);
    VecAssemblyEnd(rhs);

    if(rank==0){
        endtime=chrono::high_resolution_clock::now();
    }
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"First assemble finished, time=%14.6e s\n\n",
      chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);
    
    MatSetOption(A,MAT_NEW_NONZERO_ALLOCATION_ERR,PETSC_TRUE);

    //************************************************************************
    if(rank==0){
        starttime=chrono::high_resolution_clock::now();
    }
    
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"\nNow we do normal FEM assemble ...\n");

    NormFEMAssemble(mesh,A,rhs);

    if(rank==0){
        endtime=chrono::high_resolution_clock::now();
    }
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"Normal FEM assemble finished, time=%14.6e s\n\n",
      chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);

    
    //*********************************************
    if(rank==0){
        starttime=chrono::high_resolution_clock::now();
    }
    
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"\nNow we do scattered FEM assemble ...\n");

    ScatterFEMAssemble(mesh,U,A,rhs);

    if(rank==0){
        endtime=chrono::high_resolution_clock::now();
    }
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"Scattered FEM assemble finished, time=%14.6e s\n\n",
      chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);

    //*********************************************
    if(rank==0){
        starttime=chrono::high_resolution_clock::now();
    }
    
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"\nNow we do scattered U-V FEM assemble ...\n");

    Scatter1FEMAssemble(mesh,U,V,A,rhs);

    if(rank==0){
        endtime=chrono::high_resolution_clock::now();
    }
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"Scattered U-V FEM assemble finished, time=%14.6e s\n\n",
      chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);

    //*********************************************
    if(rank==0){
        starttime=chrono::high_resolution_clock::now();
    }
    
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"\nNow we do scattered U-V-Hist FEM assemble ...\n");

    Scatter2FEMAssemble(mesh,U,V,Proj,Hist,A,rhs);

    if(rank==0){
        endtime=chrono::high_resolution_clock::now();
    }
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"Scattered U-V-Hist FEM assemble finished, time=%14.6e s\n\n",
      chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);





    MatDestroy(&A);
    VecDestroy(&rhs);

    VecDestroy(&U);
    VecDestroy(&V);

    VecDestroy(&Proj);
    VecDestroy(&Hist);

    PetscFinalize();
    return ierr;
}