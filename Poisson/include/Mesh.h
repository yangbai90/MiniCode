#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Mesh
{
public:
    Mesh(int nx=100,double xmin=0.0,double xmax=1.0,string meshtype="edge2");
    void CreateMesh(int nx=100,double xmin=0.0,double xmax=1.0,string meshtype="edge2");

    // get mesh information
    inline double GetIthNodeJthCoord(const int &i,const int &j) const{
        return _NodeCoords[(i-1)*3+j-1];
    }
    inline int GetIthElmtJthNodeIndex(const int &i,const int &j) const{
        return _Conn[(i-1)*_nNodesPerElmt+j-1];
    }
    inline vector<int> GetIthElmtNodeIndex(const int &i) const{
        vector<int> temp;
        temp.reserve(_nNodesPerElmt);
        for(int j=0;j<_nNodesPerElmt;j++){
            temp.push_back(_Conn[(i-1)*_nNodesPerElmt+j]);
        }
        return temp;
    }

    //*************************
    void PrintMeshInfo() const;

private:
    int _Nx;
    double _Xmin,_Xmax;
    string _MeshType;
    vector<double> _NodeCoords;
    vector<int> _Conn;
    int _BCConn[2];
    int _nNodes,_nElmts,_nNodesPerElmt;

};

#endif // MESH_H