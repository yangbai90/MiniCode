#include "NonlinearSolver.h"

bool NonlinearSolver::CheckConvergence(){
    if(_Criterion==0){
        if((_Rnorm<_Ratol||_Rnorm<_Rnorm0*_Rrtol)||
           (_Enorm<_Eatol||_Enorm<_Enorm0*_Ertol)){
               return true;
        }
        else{
            return false;
        }
    }
    else if(_Criterion==1){
        if(_Rnorm<_Ratol||_Rnorm<_Rnorm0*_Rrtol){
            return true;
        }
        else{
            return false;
        }
    }
    else if(_Criterion==2){
        if(_Enorm<_Eatol||_Enorm<_Enorm0*_Ertol){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}