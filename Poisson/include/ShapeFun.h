#ifndef SHAPEFUN_H
#define SHAPEFUN_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class ShapeFun
{
public:
    ShapeFun();
    ShapeFun(int dim);
    void PreCalc();
    void Calc(const double &xi,const vector<double> &nodes) {
        Compute1DLagrangeShapeFun(xi,nodes);
    }// for 1D case
    // void Calc(const double &xi,const double &eta,const Nodes &nodes);// for 2D case
    // void Calc(const double &xi,const double &eta,const double &zeta,const Nodes &nodes);


    // // settings
    void SetDim(int dim) {_nDim=dim;_HasDim=true;}
    void SetShapeFunNum(int nnodes) {_nFuns=nnodes;}
    // void SetShapeFunType(MeshType meshtype);

    // get information
    inline int GetShapeFunNums() const {return _nFuns;}
    inline int GetDim() const {return _nDim;}
    inline int GetOrder() const {return _nOrder;}
    inline double GetDetJac() const {return _DetJac;}
    // inline MeshType GetMeshType() const {return _MeshType;}

    // operator overload
    inline double  operator()(const int &i,const int &j) const {return _values[(i-1)*(_nDim+1)+j-1];}
    inline double& operator()(const int &i,const int &j) {return _values[(i-1)*(_nDim+1)+j-1];}

    inline double shape_value(const int &i) const {return (*this)(i,0);}
    inline double shape_grad(const int &i) const {return (*this)(i,1);}


private:
    void Compute1DLagrangeShapeFun(const double &xi,const vector<double> &nodes) ;

  


private:
    int _nOrder,_nFuns;
    int _nDim;
    bool _IsCartesianDeriv;
    double _DetJac;
    double _dxdxi,_dydxi,_dzdxi;
    double _dxdeta,_dydeta,_dzdeta;
    double _dxdzeta,_dydzeta,_dzdzeta;
    double _XJac[3][3],_Jac[3][3];
    vector<double> _values;
    int _nValues;
    bool _HasDim,_HasOrder,_HasMeshType;
};


#endif 