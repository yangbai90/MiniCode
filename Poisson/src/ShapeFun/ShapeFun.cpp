#include "ShapeFun.h"

ShapeFun::ShapeFun()
{
    _nOrder=0;_nFuns=0;
    _nDim=0;
    _IsCartesianDeriv=true;// d/dX,d/dY; false-->d/dxi,d/deta...
    _HasDim=false;_HasOrder=false;_HasMeshType=false;
    _values.clear();
    _nValues=0;
}

ShapeFun::ShapeFun(int dim)
{
    _nFuns=0;
    _nDim=dim;
    _IsCartesianDeriv=true;// d/dX,d/dY; false-->d/dxi,d/deta...
    _values.clear();
    _HasDim=true;_HasOrder=true;_HasMeshType=true;
    _nValues=0;
}


void ShapeFun::PreCalc()
{
    if(_HasDim)
    {
        switch (_nFuns)
        {
            case 2:
                _nFuns=2;
                _nOrder=1;
                break;
            case 3:
                _nFuns=3;
                _nOrder=2;
                break;
            case 4:
                _nFuns=4;
                _nOrder=3;
                break;
            default:
                cout<<"*** Error: unsupported shape function type!!!"<<endl;
                break;
        }
        _nValues=(1+GetDim())*_nFuns;
        _values.resize(_nValues,0.0);
    }
    else
    {
        cout<<"*** Error: shape fun information not complete!!!"<<endl;
    }
}