#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <tuple>
#include <cassert>

using namespace std;


class SpMat{
public:
    SpMat();
    SpMat(const int &m,const int &n);

    void SetFromCooList(const vector<tuple<int,int,double>> &list);

private:
    vector<map<int,int>> _IndexMap;
    int _nRows,_nCols;// information for MxN
    int _NNZ;
    bool _IsRowAndColSet;

    // use raw pointer to interface with other library
    bool _IsMemAllocated,_IsReleased;
    vector<double> _data;
    vector<int> _indices,_indptr;
};