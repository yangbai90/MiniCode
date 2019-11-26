#include "SpMat.h"

SpMat::SpMat(){
    _IndexMap.clear();
    _IsMemAllocated=false;
    _IsReleased=true;

    _nRows=0;_nCols=0;// information for MxN
    _NNZ=0;
    _IsRowAndColSet=false;


    _data.clear();
    _indices.clear();
    _indptr.clear();
}
SpMat::SpMat(const int &m,const int &n){
    if(m<1){
        static_assert("*** Error: invalid row number for sparse matrix");
    }
    if(n<1){
        static_assert("*** Error: invalid col number for sparse matrix");
    }
    _nRows=m;_nCols=n;
    _IsRowAndColSet=true;
    _NNZ=0;
    _IsMemAllocated=false;
    _IsReleased=true;

    _data.clear();
    _indices.clear();
    _indptr.clear();
}
//***************************************
void SpMat::SetFromCooList(const vector<tuple<int,int,double>> &list){
    // set the sparse matrix from coordinate list
    // COO(row_index, col_index, value)
    if(!_IsRowAndColSet){
        static_assert("*** Error: in order to set sparse matrix from CooList, the rows and cols must be set!!!");
        abort();
    }
    // taken from: https://github.com/scipy/scipy/blob/v1.3.3/scipy/sparse/sparsetools/coo.h
    _indices.resize(_nRows+1,0);
    int nnz=int(list.size());

    int n,i,Ai,cumsum,temp;
    for(n=0;n<nnz;n++){
        Ai=get<0>(list[n]);
        _indices[Ai]++;
    }
    //cumsum the nnz per row to get Bp[](indices)
    for(i=0,cumsum=0;i<_nRows;i++){
        temp=_indices[i];
        _indices[i]=cumsum;
        cumsum+=temp;
    }
    _indices[_nRows]=nnz;

    //write Aj,Ax into Bj,Bx(to CSR format)
    int row,dest,Ai,Aj;
    double Ax;
    for(n=0;n<nnz;n++){
        tie(Ai,Aj,Ax)=list[n];

        row=Ai;
        dest=_indices[row];
        
    }
}