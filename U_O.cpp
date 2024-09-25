#include <iostream>
#include <cmath>
#include <math.h> 
#include <complex>
#include <fstream>
#include <omp.h>
#include "t-J/master.hpp"
#include "t-J/input/creat_directory.hpp"
// #include "t-J/Operator/operators.hpp"
// #include "t-J/Operator/pobopp.hpp"

using namespace std;

int main(int argc,char* argv[])
{
    int ii=atoi(argv[1]);
    int N=atoi(argv[2]);
    int nup=atoi(argv[3]);
    int ndown=atoi(argv[4]);
    int order=atoi(argv[5]);
    
    //===========================//
    //===========================//
    for (double i = 0.6; i <=1.1 ; i+=0.2)
    {
        input Data;
        Data.J1=i;
        Data.J2=1;
        Data.t1=0;
        Data.t2=0;
        Data.N=N;
        Data.nup=nup;
        Data.ndown=ndown;
        Data.longrange=1;
        Data.argument = "STATIC";
        //Data.argument = "DYNAMIC";
        Data.Master_print(ii,order);
    }
    
    //===========================//
    //===========================//
    

    //operators_NSC alpha;
    //Data.Hamiltonian();
    
}
