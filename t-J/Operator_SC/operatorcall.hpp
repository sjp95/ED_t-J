#ifndef OPERATORCALLSC_HPP_INCLUDED
#define OPERATORCALLSC_HPP_INCLUDED
#include "operators.hpp"
#include "pobopp.hpp"
#include "ni.hpp"
#include "SiSj.hpp"
#include "SjSk.hpp"
#include "dir.hpp"

using namespace std;
using namespace Eigen;

void operators_SC::output(int i,int order)
{
    //=============================//
    //=============================//
    if (order==0)
    {
        nni(i); 
    }
    if (order==1)
    {
        SiSj(i); 
    }
    if (order==2)
    {
        SjSk(i); 
    }
    //=============================//
    //=============================//

    
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
