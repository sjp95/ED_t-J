#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED
#include "math.h"
#include <complex>
#include <Eigen/Dense>
#include <vector>
#include <chrono>
//#include"Hamiltonian.hpp"
using namespace std;
using namespace Eigen;
//=======================================================//
class input
{
    public:
        long long N=12; //| == cluster size
        long long nup=5;
        long long ndown=5;

        double J1=1;
        double J2=0.1;

        double t1=-1;
        double t2=-0.1;
        int longrange=4;
        std::string argument = "STATIC";
    private:
        MatrixXd JJ=MatrixXd ::Zero(N,N);
        MatrixXd tt=MatrixXd ::Zero(N,N);
        
        VectorXi upi=VectorXi ::Zero(N);
        VectorXi downi=VectorXi ::Zero(N);
        MatrixXcd H0;
        //=========================================================//
                         //====Basis formation====//
        //=========================================================//
        long long fact(long long n);         
        long long nCr(long long n,long long r);              
        void pob_up_n(int value);        
        int pob_up_v();       
        void pob_down_n(int value);
        int pob_down_v();
        void Values();
        void Basis();
        long long le = nCr(N,nup)*nCr(N-nup,ndown);
        vector<int> basisarray;
        int find(int target);//====An algorithm to find location of a number====//
        //=========================================================//
                      //====Hamiltonian formation====//
        //=========================================================//
        
        complex<double> diagonal(int n);
        void Hamiltonian();
        void hoping_up( int i,int nn);
        void hoping_down( int i,int nn);
        void spin_hoping( int i,int nn);
        //=========================================================//
                      //====000000000000000000====//
        //=========================================================//
        
    public:
        void Master_print(int ii,int order);
        void BASIS_print();
        bool createDirectory(const std::string& path);
        

        
        
       
    

        
};



// //======================================================//
// double input:: Fermi(double e,double m)
// { 
//     return 1/(exp((e-m)/T)+1);
// }
// //=======================================================//
// double input::delta(double x0, double x)
// {
//     double L=0.15;
//     double D= (L/(2*M_PI))/(0.01+(x-x0)*(x-x0));
//     return D;
// }
// //=======================================================//
// void input:: Partition_function()
// { 
//     Z=0.0;
//     for(int i=0;i<es.size();i++)
//     {
//         Z+=exp(-(es(i)-es(0))/T);
//     }
// }
// //======================================================//
#endif