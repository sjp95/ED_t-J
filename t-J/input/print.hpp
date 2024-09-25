#ifndef PRINT_HPP_INCLUDED
#define PRINT_HPP_INCLUDED
#include <math.h>
#include <complex>
#include <Eigen/Dense>
#include <vector>
#include <omp.h>
#include <string>
#include "input.hpp"

using namespace std;
using namespace Eigen;
//================================================================================//
//================================================================================//

  void input::BASIS_print()
  {
    std::cout<< "Basis states: " <<endl;
    std::cout<< "======================================================" <<endl;
    for (int target : basisarray)
    {
        int location =find(target);

        int x= nCr(N,nup);
        int vup= int(target%x);
        int vdown=int(target/x);

        pob_up_n(vup);
        pob_down_n(vdown);

        cout<< target<<" |"<<upi.transpose()<<"> |"<<downi.transpose()<<"> "<<endl;
    }
    std::cout<< "======================================================" <<endl; 
  }


//================================================================================//
//================================================================================//
#endif
