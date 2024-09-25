#ifndef OERATORSSC_HPP_INCLUDED
#define OERATORSSC_HPP_INCLUDED
#include "math.h"
#include <complex>
#include <Eigen/Dense>
#include <vector>
#include <chrono>
//#include"Hamiltonian.hpp"
using namespace std;
using namespace Eigen;
//=======================================================//
class operators_SC
{
    public:
        double J1=1;
        double J2=0.1;

        double t1=-1;
        double t2=-0.1;
        
        long long N=2; //| == cluster size
        long long nup=2;
        long long ndown=2;
        long long le0 =1;// nCr(N,nup)*nCr(N-nup,ndown);
        // long long leup =1;// nCr(N,nup+1)*nCr(N-nup-1,ndown-1);
        // long long ledown =1;// nCr(N,nup-1)*nCr(N-nup+1,ndown+1);

        MatrixXd JJ=MatrixXd ::Zero(N,N);
        MatrixXd tt=MatrixXd ::Zero(N,N);
        int longrange=4;

        vector<int> basisarray0;
        // vector<int> basisarray_up;
        // vector<int> basisarray_down;

        VectorXcd evs_0 = VectorXcd :: Zero(le0);
        VectorXd es_0 = VectorXd :: Zero(le0);

        // MatrixXcd evs_up = MatrixXcd :: Zero(leup,leup);      //             | A
        // VectorXd es_up = VectorXd :: Zero(leup);

        // MatrixXcd evs_down = MatrixXcd :: Zero(ledown,ledown);      //             | A
        // VectorXd es_down = VectorXd :: Zero(ledown);
        
        double delta(double x0, double x);
        void output(int i,int order);
        bool createDirectory(const std::string& path);

    private:
       long long fact(long long n);         
       long long nCr(long long n,long long r);  
       void pob_up_n(int value);        
       int pob_up_v();       
       void pob_down_n(int value);
       int pob_down_v(); 

       VectorXi upi=VectorXi ::Zero(N);
       VectorXi downi=VectorXi ::Zero(N); 
       int find0(int target);//====An algorithm to find location of a number====//
    //    int find_up(int target);
    //    int find_down(int target);
       //=========================================================//
                          //====SC====//
       //=========================================================//
       void nni(int ii);
       pair<complex<double>, complex<double>> change_NI(int ii,int nn0,int f0);
       
       pair<complex<double>, complex<double>> change_SISJ(int ii,int jj,int nn0,int f0);
       void SiSj(int ii);

        pair<complex<double>, complex<double>> change_SJSK(int ii,int jj,int kk,int nn0,int f0);
         void SjSk(int ii);
       //=========================================================//
                          //====SC====//
       //=========================================================//
       
    //=========================================================//
                    //====000000000000000000====//
    //=========================================================//
                
};

//=================== General input ====================//
double operators_SC::delta(double x0, double x)
{
    double L=0.15;
    double D= (L/(2*M_PI))/(0.01+(x-x0)*(x-x0));
    return D;
}
//=================== General input ====================//




#endif