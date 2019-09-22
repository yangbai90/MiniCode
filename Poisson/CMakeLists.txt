cmake_minimum_required(VERSION 3.8)
project(AsFem)

set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("/home/by/Programs/Eigen")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
##############################################
### For debug mode                         ###
##############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O2 -Wall -Wextra -Werror")

##############################################
### For release mode                       ###
##############################################
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3 -Wall -march=native -DNDEBUG")

#####################################################################
### In most cases, you don't need to modify the following lines!!!###
### In most cases, you don't need to modify the following lines!!!###
### In most cases, you don't need to modify the following lines!!!###
#####################################################################
set(src src/main.cpp)
set(inc include/Welcome.h)

#####################################################################
### For Mesh                                                      ###
#####################################################################
set(inc ${inc} include/Mesh.h)
set(src ${src} src/Mesh/Mesh.cpp src/Mesh/CreateMesh.cpp)
set(src ${src} src/Mesh/PrintMeshInfo.cpp)


#####################################################################
### For dof handler                                               ###
#####################################################################
set(inc ${inc} include/DofHandler.h)
set(src ${src} src/DofHandler/DofHandler.cpp src/DofHandler/CreateDofMap.cpp)
set(src ${src} src/DofHandler/PrintDofMap.cpp)


#####################################################################
### For equation system                                           ###
#####################################################################
set(inc ${inc} include/EquationSystem.h)
set(src ${src} src/EquationSystem/EquationSystem.cpp)
set(src ${src} src/EquationSystem/InitEquationSystem.cpp)
set(src ${src} src/EquationSystem/CreateSparsityPattern.cpp)


#####################################################################
### For nonlinear solver                                          ###
#####################################################################
set(inc ${inc} include/NonlinearSolver.h)
set(src ${src} src/NonlinearSolver/NonlinearSolver.cpp)
set(src ${src} src/NonlinearSolver/Solve.cpp)
set(src ${src} src/NonlinearSolver/NonLinearSolve.cpp)
set(src ${src} src/NonlinearSolver/NewtonRaphson.cpp)
set(src ${src} src/NonlinearSolver/CheckConvergence.cpp)

#####################################################################
### For nonlinear solver                                          ###
#####################################################################
set(inc ${inc} include/SolutionSystem.h)
set(src ${src} src/SolutionSystem/SolutionSystem.cpp)

#####################################################################
### For FE                                                        ###
#####################################################################
set(inc ${inc} include/ShapeFun.h)
set(src ${src} src/ShapeFun/ShapeFun.cpp)
set(src ${src} src/ShapeFun/Compute1DLagrangeShapeFun.cpp)

set(inc ${inc} include/QPoint.h)
set(src ${src} src/QPoint/QPoint.cpp)
set(src ${src} src/QPoint/Create1DGaussPoint.cpp)

#####################################################################
### For elmt system                                               ###
#####################################################################
set(inc ${inc} include/ElmtSystem.h)
set(src ${src} src/ElmtSystem/ElmtLib.cpp)
set(src ${src} src/ElmtSystem/Poisson.cpp)

#####################################################################
### For BC system                                                 ###
#####################################################################
set(inc ${inc} include/BCSystem.h)
set(src ${src} src/BCSystem/BCSystem.cpp)
set(src ${src} src/BCSystem/SetBC.cpp)
set(src ${src} src/BCSystem/PrintBCInfo.cpp)
set(src ${src} src/BCSystem/ApplyBC.cpp)

#####################################################################
### For FESystem                                                  ###
#####################################################################
set(inc ${inc} include/FESystem.h)
set(src ${src} src/FESystem/FormKR.cpp)
set(src ${src} src/FESystem/Init.cpp)


##########################################
add_executable(asfem ${inc} ${src})

