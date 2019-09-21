#ifndef QPOINT_H
#define QPOINT_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>


using namespace std;

class QPoint
{
public:
    QPoint();
    QPoint(int dim,int order);


    void SetDim(int dim) {_nDim=dim;}
    void SetQPointOrder(int order) {_nOrder=order;}
    void CreateQPoints(){Create1DGaussPoint();}

    // get function
    inline int GetDim() const {return _nDim;}
    inline int GetQpOrder() const {return _nOrder;}
    inline int GetQpPointsNum() const {return _nQpPoints;}
    
    inline double operator()(int i,int j) const {return _qp_coords[(i-1)*(_nDim+1)+j];}
    inline double& operator()(int i,int j) {return _qp_coords[(i-1)*(_nDim+1)+j];}

    inline double GetIthQpPointJthCoord(int i,int j) const {return _qp_coords[(i-1)*(_nDim+1)+j];}

private:
    void Create1DGaussPoint();
    // void Create1DGaussLobattoPoint();

    // void Create2DGaussPoint(MeshType meshtype);
    // void Create2DGaussLobattoPoint(MeshType meshtype);

    // void Create3DGaussPoint(MeshType meshtype);
    // void Create3DGaussLobattoPoint(MeshType meshtype);

private:
    vector<double> _qp_coords;
    int _nQpPoints,_nOrder;
    int _nDim;
    bool _HasSettings=false;
    bool _HasDim,_HasOrder;

};

#endif 