#include "Mesh.h"


Mesh::Mesh(int m,int n){
    _Nx=m;_Ny=n;
    _nElmts=_Nx*_Ny;
    _nNodesPerElmt=9;

    _nNodes=(2*_Nx+1)*(2*_Ny+1);
}

void Mesh::CreateMesh(){
    int i,j,k;
    int e,i1,i2,i3,i4,i5,i6,i7,i8,i9;
    _NodeCoords.resize(_nNodes*3,0.0);
    _Conn.resize(_nElmts*_nNodesPerElmt,0);

    const double dx=0.1;
    const double dy=0.1;

    for(j=1;j<=2*_Ny+1;++j){
        for(i=1;i<=2*_Nx+1;++i){
            k=(j-1)*(2*_Nx+1)+i;
            _NodeCoords[(k-1)*3+1-1]=0.0+(i-1)*dx;
            _NodeCoords[(k-1)*3+2-1]=0.0+(j-1)*dy;
            _NodeCoords[(k-1)*3+3-1]=0.0;
        }
    }

    for(j=1;j<=_Ny;++j){
        for(i=1;i<=_Nx;++i){
            e=(j-1)*_Nx+i;
            i1=(j-1)*2*(2*_Nx+1)+2*i-1;
            i2=i1+2;
            i3=i2+2*(2*_Nx+1);
            i4=i3-2;

            i5=i1+1;
            i6=i2+(2*_Nx+1);
            i7=i3-1;
            i8=i1+(2*_Nx+1);
            i9=i8+1;

            _Conn[(e-1)*_nNodesPerElmt+1-1]=i1;
            _Conn[(e-1)*_nNodesPerElmt+2-1]=i2;
            _Conn[(e-1)*_nNodesPerElmt+3-1]=i3;
            _Conn[(e-1)*_nNodesPerElmt+4-1]=i4;
            _Conn[(e-1)*_nNodesPerElmt+5-1]=i5;
            _Conn[(e-1)*_nNodesPerElmt+6-1]=i6;
            _Conn[(e-1)*_nNodesPerElmt+7-1]=i7;
            _Conn[(e-1)*_nNodesPerElmt+8-1]=i8;
            _Conn[(e-1)*_nNodesPerElmt+9-1]=i9;
        }
    }
}