#ifndef DOFHANDLER_H
#define DOFHANDLER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DofHandler{
public:
    DofHandler();
    void CreateDofMap(int ndofspernode);
};

#endif // DOFHANDLER_H