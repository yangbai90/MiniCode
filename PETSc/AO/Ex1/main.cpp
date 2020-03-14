#include <iostream>
#include "petsc.h"

#include "Mesh.h"

using namespace std;

int main(int args,char *argv[]){
    PetscErrorCode ierr;
    Mat A;
    // AO ao;
    PetscMPIInt rank,size;


    ierr=PetscInitialize(&args,&argv,NULL,NULL);

    Mesh mesh(500,500);
    mesh.CreateMesh();

    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"*** Number of nodes=%8d, number of elmts=%8d\n",mesh.GetNodesNum(),mesh.GetElmtsNum());


    // MatCreate(PETSC_COMM_WORLD,&A);
    // MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,mesh.GetNodesNum(),mesh.GetNodesNum());
    MatCreateAIJ(PETSC_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,mesh.GetNodesNum(),mesh.GetNodesNum(),4*9,NULL,4*9,NULL,&A);
    MatSetFromOptions(A);
    MatSetUp(A);

    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    int rankne=mesh.GetElmtsNum()/size;
    int eStart=rank*rankne;
    int eEnd=eStart+rankne;
    if(rank==size-1) eEnd=mesh.GetElmtsNum();
    int ei,e,i,j;

    for(ei=eStart;ei<eEnd;++e){
        e=ei+1;
        for(i=1;i<=9;++i){
            for(j=1;j<=9;++j){
                
            }
        }       
    }
    




    PetscFinalize();
    return ierr;
}