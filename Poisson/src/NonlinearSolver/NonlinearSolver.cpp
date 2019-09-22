#include "NonlinearSolver.h"

NonlinearSolver::NonlinearSolver(){
    _MaxIters=15;_Criterion=0;
    _Rrtol=1.0e-9;_Ratol=1.0e-8;
    _Ertol=1.0e-16;_Eatol=1.0e-15;
    _Rnorm0=1.0;_Rnorm=1.0;
    _Enorm0=1.0;_Enorm=1.0;
    _Method=NonLinearMethod::NEWTONRAPHSON;
}

void NonlinearSolver::Init(){
    _MaxIters=15;_Criterion=0;
    _Rrtol=1.0e-9;_Ratol=1.0e-8;
    _Ertol=1.0e-16;_Eatol=1.0e-15;
    _Rnorm0=1.0;_Rnorm=1.0;
    _Enorm0=1.0;_Enorm=1.0;
    _Method=NonLinearMethod::NEWTONRAPHSON;
}