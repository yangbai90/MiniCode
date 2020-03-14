#include <iostream>
#include "petsc.h"

using namespace std;

int main(int args,char *argv[]){
    PetscMPIInt rank;
    PetscInt M=10, N=8;
    PetscErrorCode ierr;
    DM da;
    PetscViewer viewer;
    Vec local,global;

    PetscInitialize(&args,&argv,NULL,NULL);
    PetscViewerDrawOpen(PETSC_COMM_WORLD,0,"",300,0,300,300,&viewer);
    

    DMDACreate2d(PETSC_COMM_WORLD,DM_BOUNDARY_NONE,DM_BOUNDARY_NONE,DMDA_STENCIL_BOX,M,N,PETSC_DECIDE,PETSC_DECIDE,1,1,NULL,NULL,&da);
    DMSetFromOptions(da);
    DMSetUp(da);
    DMCreateGlobalVector(da,&global);
    DMCreateLocalVector(da,&local);

    VecSet(global,-3.0);
    DMGlobalToLocalBegin(da,global,INSERT_VALUES,local);
    DMGlobalToLocalEnd(da,global,INSERT_VALUES,local);

    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);
    VecScale(local,1+rank);
    DMLocalToGlobalBegin(da,local,ADD_VALUES,global);
    DMLocalToGlobalEnd(da,local,ADD_VALUES,global);

    VecView(global,PETSC_VIEWER_STDOUT_WORLD);

    DMView(da,viewer);
    DMView(da,PETSC_VIEWER_STDOUT_WORLD);
    VecView(global,viewer);


    PetscViewerDestroy(&viewer);
    VecDestroy(&local);
    VecDestroy(&global);
    ierr=DMDestroy(&da);
    PetscFinalize();
    return ierr;
}