#include "Mesh.h"

Mesh::Mesh(int nx,double xmin,double xmax,string meshtype){
    _Nx=nx;
    if(nx<1)
    {
        cout<<"Error: nx="<<nx<<" is invalid!!!"<<endl;
    }
    _Xmin=xmin;_Xmax=xmax;
    _MeshType=meshtype;
    if(meshtype!="edge2"&&meshtype!="edge3"&&meshtype!="edge4"){
        cout<<"Error: meshtype="<<meshtype<<" is invalid!!!"<<endl;
    }
    _NodeCoords.clear();
    _Conn.clear();
    _BCConn[0]=1;_BCConn[1]=1;
    _nNodes=0;_nElmts=0;_nNodesPerElmt=0;
}