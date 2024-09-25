#include <iostream>
#include <cmath>
#include <math.h> 
#include <complex>
#include <fstream>
#include <omp.h>
#include "Data/NSC/NSCorder.hpp"
#include "Data/NSC/consolidate.hpp"
// #include "t-J/master.hpp"
// #include "t-J/input/creat_directory.hpp"
// #include "t-J/Operator/operators.hpp"
// #include "t-J/Operator/pobopp.hpp"

using namespace std;

int main(int argc,char* argv[])
{
    int N=atoi(argv[1]);
    int nup=atoi(argv[2]);
    int ndown=atoi(argv[3]);
    int ttt0=atoi(argv[4]);
    int ttt1=atoi(argv[5]);
    int jjt0=atoi(argv[6]);
    int jjt1=atoi(argv[7]);

    
    
    //===========================//
    //===========================//
    NSC_input Data;
    Data.N=N;
    Data.nup=nup;
    Data.ndown=ndown;
    Data.ttt0=ttt0;
    Data.ttt1=ttt1;
    Data.jjt0=jjt0;
    Data.jjt1=jjt1;

    if(strcmp(argv[8], "c") == 0)
    {
        Data.Consolidet_NSC();
    }
    else
    {
        int order=atoi(argv[8]);
        Data.Data_of_order(order);
    }
    
   
    //===========================//
    //===========================//
    

    //operators_NSC alpha;
    //Data.Hamiltonian();
    
}
