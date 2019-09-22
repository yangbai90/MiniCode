#include <iostream>

#include "Eigen/Eigen"


using namespace std;

double operator*(const Eigen::Vector3d &a,const Eigen::Vector3d &b){
    return a(0)*b(0)+a(1)*b(1)+a(2)*b(2);
}


int main()
{
    Eigen::Vector3d a,b;
    a(0)=1.0;a(1)=2.0;a(2)=3.0;
    b(0)=1.0;b(1)=1.0;b(2)=1.0;
    cout<<"a*b="<<a*b<<endl;
    // return 0;
}
