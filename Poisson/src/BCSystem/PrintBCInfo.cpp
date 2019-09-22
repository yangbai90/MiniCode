#include "BCSystem.h"

void BCSystem::PrintBCInfo() const{
    printf("*** Boundary condition information:\n");
    for(unsigned int i=0;i<_BCInfo.size();++i){
        printf("*** side=%12s, type=%12s, value=%12.5e\n",_BCInfo[i].first.c_str(),
                                                          _BCInfo[i].second.c_str(),
                                                          _BCValue[i]);
    }
}