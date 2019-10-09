#include <iostream>
#include <ctime>

#include "viennacl/vector.hpp"
#include "viennacl/tools/timer.hpp"

using namespace std;

int main(){
    cout<<"Hi"<<endl;
    viennacl::vector<double> vl_vec;
    vector<double> std_vec;
    double res;
    const int n=50000000;
    srand(time(0));
    vl_vec.resize(n,0.0);
    std_vec.reserve(n);
    cout<<"size="<<vl_vec.size()<<endl;
    for(unsigned int i=0;i<vl_vec.size();++i){
        vl_vec[i]=1.0*rand()/RAND_MAX;
        std_vec.push_back(vl_vec[i]);
    }
    viennacl::tools::timer tstart;
    tstart.start();
    viennacl::linalg::norm_2_cpu(vl_vec,res);
    cout<<"norm2(viennacl)="<<res<<",using time="<<tstart.get()<<endl;
    viennacl::tools::timer tstart1;
    tstart1.start();
    res=0.0;
    for(unsigned int i=0;i<std_vec.size();++i){
        res+=std_vec[i]*std_vec[i];
    }
    res=sqrt(res);
    cout<<"norm2(std)="<<res<<",using time="<<tstart1.get()<<endl;
    return 0;
}