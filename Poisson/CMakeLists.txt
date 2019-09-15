cmake_minimum_required(VERSION 3.8)
project(AsFem)

set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/Eigen")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
##############################################
### For debug mode                         ###
##############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O2 -Wall -Wextra")

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
set(src ${src} src/DofHandler/DofHandler.cpp)

#########################################3
add_executable(asfem ${inc} ${src})

