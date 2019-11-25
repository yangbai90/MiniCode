cmake_minimum_required(VERSION 3.8)
project(AsFem)

set(CMAKE_CXX_STANDARD 14)

set(VL "/home/by/Programs/viennacl")
set(Eigen "/home/by/Programs/Eigen")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${VL}")
include_directories("${Eigen}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
##############################################
### For debug mode                         ###
##############################################
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O2 -Wall -Wextra -Werror -DVIENNACL_WITH_OPENMP")

##############################################
### For release mode                       ###
##############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3 -Wall -march=native -DNDEBUG -DVIENNACL_WITH_OPENMP")


set(src main.cpp)




##########################################
add_executable(asfem ${src})

