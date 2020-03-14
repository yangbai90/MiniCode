#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Mesh{
public:
    Mesh(int m,int n);
    void CreateMesh();

    inline int GetNodesNum()const{return _nNodes;}
    inline int GetElmtsNum()const{return _nElmts;}
    inline int GetIthElmtJthIndex(const int &i,const int &j)const{return _Conn[(i-1)*_nNodesPerElmt+j-1];}

private:
    int _Nx,_Ny;
    int _nNodes,_nElmts,_nNodesPerElmt;
    vector<double> _NodeCoords;
    vector<int> _Conn;
};