#ifndef OPERATORCALL_HPP_INCLUDED
#define OPERATORCALL_HPP_INCLUDED
#include "operators.hpp"
#include "pobopp.hpp"
#include "Sxi.hpp"
#include "SxiSiSj.hpp"
#include "SxiSjSk.hpp"
#include "StaticSZ.hpp"
#include "dir.hpp"
#include "ni.hpp"
using namespace std;
using namespace Eigen;

void operators_NSC::output(int i,int order)
{
    //=============================//
    //=============================//
    for (char& c : argument) {
        c = std::toupper(c);
    }
    //=============================//
    //=============================//
    if (argument == "DYNAMIC")
    {
        if (order==0)
        {
            Sx(i); 
        }
        if (order==1)
        {
            SxiSiSj(i); 
        }
        if (order==2)
        {
            SxiSjSk(i); 
        }
    }
    if (argument == "STATIC")
    {
        Static_SZ(i); 
    }
    

    //=============================//
    //=============================//


    //nni(i); 
    
    //--------------------------------------------------//
    // cout<< "======================================================" <<endl; 
    // cout<<"J: \n" <<JJ <<"\n"<<endl;
    // cout<< "======================================================" <<endl; 
    // cout<<"t: \n" <<tt <<"\n"<<endl;
    // cout<< "======================================================" <<endl; 
    // cout<< "length of the interaction: "<< longrange <<endl;
    // cout<< "======================================================" <<endl; 
    // cout<<"n_up:  "<<nup <<endl;
    // cout<<"n_down:  "<<nup <<endl;
    // cout<<"Hilbertspace dimention:  "<<le0<<"\n"<<endl;
    // cout<< "======================================================" <<endl; 
    //--------------------------------------------------//
}


#endif
