#include <iostream>
#include <ctime>

#include "viennacl/vector.hpp"
#include "viennacl/tools/timer.hpp"

#include "Eigen/Eigen"

using namespace std;

int main(){
    viennacl::vector<double> vl_vec;
    vector<double> std_vec;
    double res;
    const int n=2000000;
    const int steps=15;
    srand(time(0));
    vl_vec.resize(n,0.0);
    std_vec.resize(n,0.0);
    Eigen::VectorXd eig_vec(n);
    cout<<"size="<<vl_vec.size()<<endl;

    viennacl::tools::timer tstart;

    double eigen_time=0.0,vl_time=0.0,std_time=0.0;

    for(int nstep=1;nstep<=steps;++nstep){
        cout<<"*** start "<<nstep<<"-step ..."<<endl;
        for(unsigned int i=0;i<vl_vec.size();++i){
            vl_vec[i]=1.0*rand()/RAND_MAX;
            std_vec[i]=vl_vec[i];
            eig_vec.coeffRef(i)=vl_vec[i];
        }
        cout<<"*** fill vector finished in step-"<<nstep<<endl;

    
        tstart.start();
        viennacl::linalg::norm_2_cpu(vl_vec,res);
        cout<<"***     norm2(viennacl)="<<res<<",using time="<<tstart.get()<<endl;
        vl_time+=tstart.get();

        tstart.start();
        cout<<"***     norm2(eigen)="<<eig_vec.norm()<<",using time="<<tstart.get()<<endl;
        eigen_time+=tstart.get();

        tstart.start();
        res=0.0;
        for(unsigned int i=0;i<std_vec.size();++i){
            res+=std_vec[i]*std_vec[i];
        }
        res=sqrt(res);
        cout<<"***     norm2(std)="<<res<<",using time="<<tstart.get()<<endl;
        std_time+=tstart.get();
    }
    printf("Final time: Std(%14.6e), Eigen(%14.6e), Viennacl(%14.6e)\n",std_time,eigen_time,vl_time);
    printf("Final average time: Std(%14.6e), Eigen(%14.6e), Viennacl(%14.6e)\n",std_time/steps,eigen_time/steps,vl_time/steps);
    return 0;
}