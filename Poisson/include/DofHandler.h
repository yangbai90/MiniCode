#ifndef DOFHANDLER_H
#define DOFHANDLER_H

#include <iostream>
#include <string>
#include <vector>

#include "Mesh.h"

using namespace std;

class DofHandler{
public:
    DofHandler();
    void CreateDofMap(int ndofspernode,Mesh &mesh);

    // get information
    inline int GetIthNodeDofIndex(const int &i,const int &j) const {return _NodalDofMap[(i-1)*_nDofsPerNode+j-1];}
    inline void GetIthElmtDofIndex(const int &e,int (&dofconn)[27]){
        for(int i=0;i<_nDofsPerElmt;++i){
            dofconn[i]=_ElmtDofMap[(e-1)*_nDofsPerElmt+i];
        }
    }
    inline vector<int> GetIthElmtDofIndex(const int &e) const{
        vector<int> temp;
        temp.reserve(_nDofsPerElmt);
        for(int i=0;i<_nDofsPerElmt;++i){
            temp.push_back(_ElmtDofMap[(e-1)*_nDofsPerElmt+i]);
        }
        return temp;
    }
    inline int GetIthElmtJthDofIndex(const int &i,const int &j) const{
        return _ElmtDofMap[(i-1)*_nDofsPerElmt+j-1];
    }

    // print information
    void PrintDofMap() const;

private:
    int _nDofsPerNode,_nDofsPerElmt;
    int _nNodes,_nElmts,_nDofs,_nNodesPerElmt;
    vector<int> _NodalDofMap;
    vector<int> _ElmtDofMap;
};

#endif // DOFHANDLER_H