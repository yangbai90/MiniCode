cmake_minimum_required(VERSION 3.8)
project(AsFem)

set(CMAKE_CXX_STANDARD 17)

###############################################
### Set your PETSc path here                ###
###############################################
set(PETSC_DIR "/home/by/Programs/petsc/3.13.5")
set(MPI_DIR "/home/by/Programs/mpich/3.3.2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# For PETSc
include_directories("${PETSC_DIR}/include")
link_libraries("${PETSC_DIR}/lib/libpetsc.so")
# For MPI
include_directories("${MPI_DIR}/include")
link_libraries("${MPI_DIR}/lib/libmpi.so")

###############################################
### For debug mode                          ###
###############################################
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fopenmp -O2")


###############################################
### For release mode                        ###
###############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fopenmp -O3 -march=native -DNDEBUG")

 



###############################################
### For all the source code                 ###
###############################################
set(src main.cpp)
#set(src ${src} Mesh.h Mesh.cpp TestFuns.h)




##################################################
add_executable(asfem ${src})

