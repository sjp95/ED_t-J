#ifndef StaticSZ_HPP_INCLUDED
#define StaticSZ_HPP_INCLUDED
#include <iomanip>
#include <cmath>
#include <math.h> 
#include <complex>
#include <Eigen/Dense>
#include <fstream>
#include <Eigen/Dense>
#include <complex>
#include "operators.hpp"
#include "pobopp.hpp"
#include "dir.hpp"
using namespace Eigen;
using namespace std;



complex<double> operators_NSC::Static_SZZ(int ii,int jj,int nn0)
{
    complex<double> fog=complex<double>(0,0);
    //===========================//
    int n = basisarray0[nn0];
    int x= nCr(N,nup);
    int vup= int(n%x);
    int vdown=int(n/x);
    //===========================//
    //===========================//
    pob_up_n(vup);
    pob_down_n(vdown);
    int aupi=upi(ii);
    int adowni=downi(ii);

    int aupj=upi(jj);
    int adownj=downi(jj);
     
    double ds1=double((aupi-adowni)*(aupj-adownj));
  
    fog=pow(abs(evs_0(nn0)),2)*0.25*ds1;
    //=======================================================//
    return  fog;
}
//=====================================================================================================================================================================//
void operators_NSC::Static_SZ(int ii)
{
    char title0[150];
    //----------------------------------------------//
    int tut0=int(t1*100);                         //| ==== File | F
    int tut1=int(t2*100);
    int tut2=int(J1*100);                         //| ==== File | F
    int tut3=int(J2*100);
    bool path= createDirectory("../Data");
    path= createDirectory("../Data/NSC");
    path= createDirectory("../Data/NSC/Static");
    sprintf(title0,"../Data/NSC/Static/SZ_%d_%d_%d_%d_%lld_%lld_%lld_%d.dat",tut0,tut1,tut2,tut3,N,nup,ndown,ii); //| ==== Name | I
    std::ofstream file;               //| ==== File | L
    file.open(title0);                //| ==== Open | E
    //----------------------------------------------//
    file << std::fixed << std::setprecision(16);
    //----------------------------------------------//

    for (int jj = 0; jj < N; jj++)
    {
          complex<double> fog_up=complex<double>(0,0);
           //cout<< f0<<"      "<<ii <<endl;
           
            for (int nn0 = 0; nn0 < le0; nn0++)
            {
                int vup= int(nn0);
                int nup1=nup;
                int ndown1=ndown;
                //============================================================//
                //============================================================//
                //pair<complex<double>, complex<double>>fog=Static_SZZ(ii,jj,nn0);
                fog_up+=Static_SZZ(ii,jj,nn0);
                //+fog_down+=fog.second;
                //============================================================//
                //============================================================//
                nup=nup1;
                ndown= ndown1;
                //cout<< f0<<"      "<<ii <<"     "<<nn0<< "      "<<fog<<endl;
                //cout<< nn0<<endl;
                //=======================================================//
            }

         file<< ii << "      "<<jj<< "      "<<fog_up.real()<< "      "<<fog_up.imag()<<endl;
         //cout<< f0 << "      "<<ii<< "      "<<fog<< "      "<<es_up(f0)-es_0<<endl;
        //cout<< "    " <<endl;
    }
    
   file.close();
}
//========================================================//

#endif
