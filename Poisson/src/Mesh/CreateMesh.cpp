#include "Mesh.h"

void Mesh::CreateMesh(int nx,double xmin,double xmax,string meshtype)
{
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

    //******************************************
    //*** start to create mesh
    //******************************************
    int P=1;
    if(_MeshType=="edge2"){
        P=1;
        _nNodesPerElmt=2;
    }
    else if(_MeshType=="edge3"){
        P=2;
        _nNodesPerElmt=3;
    }
    else if(_MeshType=="edge4"){
        P=3;
        _nNodesPerElmt=4;
    }

    _nElmts=nx;
    _nNodes=_nElmts*P+1;

    double dx=(_Xmax-_Xmin)/(_nNodes-1);

    int i,e;
    _NodeCoords.reserve(_nNodes*3);
    _Conn.reserve(_nElmts*_nNodesPerElmt);
    for(i=0;i<_nNodes;i++){
        _NodeCoords.push_back(_Xmin+i*dx);
        _NodeCoords.push_back(0.0);
        _NodeCoords.push_back(0.0);
    }

    for(e=0;e<_nElmts;++e){
        for(i=1;i<=_nNodesPerElmt;i++){
            _Conn.push_back(e*P+i);
        }
    }

    _BCConn[0]=1;_BCConn[1]=_nNodes;
}