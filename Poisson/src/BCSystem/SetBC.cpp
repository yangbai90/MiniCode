#include "BCSystem.h"

void BCSystem::SetBC(string sidename,string bctype,double bcvalue){
    if(_BCInfo.size()==0&&_BCValue.size()==0){
        _BCInfo.push_back(make_pair(sidename,bctype));
        _BCValue.push_back(bcvalue);
    }
    else{
        bool IsInList=false;
        for(auto it:_BCInfo){
            if(it.first==sidename&&it.second==bctype){
                cout<<"*** Error: duplicated boundary condition!!!"<<endl;
                cout<<"***        side="<<it.first<<", type="<<it.second<<endl;
                IsInList=true;
            }
        }
        if(!IsInList){
            _BCInfo.push_back(make_pair(sidename,bctype));
            _BCValue.push_back(bcvalue);
        }
    }
}