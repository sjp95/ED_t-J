#ifndef HAMILTONIAN_HPP_INCLUDED
#define HAMILTONIAN_HPP_INCLUDED
#include <math.h>
#include "../input/input.hpp"
#include "../input/pob.hpp"
#include <Eigen/Dense>
#include "hopping.hpp"
#include <complex>
using namespace std;
using namespace Eigen;


//================================================//
            //=== Diagonal element ===//
//================================================//
complex<double> input::diagonal(int n)
{

    int x= nCr(N,nup);
    int vup= int(n%x);
    int vdown=int(n/x);

    pob_up_n(vup);
    pob_down_n(vdown);

    complex <double> D0=complex <double>(0,0);
    for ( int i =0; i<N; i++)
    {
        complex <double> Di=complex<double>(upi(i)-downi(i));
        for ( int j =i+1; j<=i+longrange; j++)
        {
           
           complex <double> Dj=complex<double>(upi(j%N)-downi(j%N));
           D0+=JJ(i,j%N)*(Di*Dj*0.25); //-0.25*abs(Di*Dj)
        //    cout<<JJ(i,j%N)*(Di*Dj*0.25)<<endl;
        }
    }
    // cout<<"     " <<D0 << endl;
    return D0;

}


//================================================//
          //=== Hamiltonian Formation ===//
//================================================//
void input::Hamiltonian()
{
    //cout<< le <<"   "<<basisarray.size()<<endl;
    H0 = MatrixXcd :: Zero(le,le);
    for (int i=0;i<le;i++)
    {
        // cout<< i << endl;
        H0(i,i) =diagonal(basisarray[i]);
        hoping_up(basisarray[i],i);
        hoping_down(basisarray[i],i);
        spin_hoping(basisarray[i],i);
    }
}
//================================================//
//================================================//
#endif


//================================================//
//================================================//
    // int Decimal(long long n)
    // {
    //     int decimalNumber = 0, i = 0, remainder;
    //     while (n!=0)
    //     {
    //         remainder = n%10;
    //         n /= 10;
    //         decimalNumber += remainder*pow(L,i);
    //         ++i;
    //     }
    //     return decimalNumber;
    // }
//================================================//
//================================================//
