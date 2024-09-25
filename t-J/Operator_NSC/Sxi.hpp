#ifndef SXI_HPP_INCLUDED
#define SXI_HPP_INCLUDED
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



pair<complex<double>, complex<double>> operators_NSC::change_SX(int ii,int nn0,int f0)
{
    complex<double> fog_up1=complex<double>(0,0);
    //complex<double> fog_up2=complex<double>(0,0);
    complex<double> fog_down1=complex<double>(0,0);
    //complex<double> fog_down2=complex<double>(0,0);
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


    if(upi(ii)+downi(ii)>0)
    {
        //======================//
        //======================//
        upi(ii)=1-upi(ii);
        downi(ii)=1-downi(ii);
        //======================//
        //======================//

        if(aupi>adowni)
        {
            nup=nup-1;
            ndown=ndown+1;
            x= nCr(N,nup);
            //=================================================================//
            int q=int(pob_down_v()*x+pob_up_v()); // Reconstruction of the new basis
            q=find_down(q);   // finding the new basis location
            //=================================================================//
            fog_down1=conj(evs_down(q,f0))*evs_0(nn0)*0.5;
        }
        //========================================================================================================================================//
        if(aupi<adowni)
        {
            nup=nup+1;
            ndown=ndown-1;
            x= nCr(N,nup);
            //=================================================================//
            int q=int(pob_down_v()*x+pob_up_v()); // Reconstruction of the new basis
            q=find_up(q);   // finding the new basis location
            //=================================================================//
            fog_up1=conj(evs_up(q,f0))*evs_0(nn0)*0.5;//+(1.0-ds1)*evs_up(a1,f0)
        }
    //=======================================================//
    //=======================================================//
    }
    //=======================================================//
    return  make_pair(fog_up1,fog_down1);
}
//=====================================================================================================================================================================//
void operators_NSC::Sx(int ii)
{
    char title0[150];
    //----------------------------------------------//
    int tut0=int(t1*100);                         //| ==== File | F
    int tut1=int(t2*100);
    int tut2=int(J1*100);                         //| ==== File | F
    int tut3=int(J2*100);
    bool path= createDirectory("../Data");
    path= createDirectory("../Data/NSC");
    path= createDirectory("../Data/NSC/SX");
    sprintf(title0,"../Data/NSC/SX/SX_%d_%d_%d_%d_%lld_%lld_%lld_%d.dat",tut0,tut1,tut2,tut3,N,nup,ndown,ii); //| ==== Name | I
    std::ofstream file;               //| ==== File | L
    file.open(title0);                //| ==== Open | E
    //----------------------------------------------//
    file << std::fixed << std::setprecision(16);
    //----------------------------------------------//

    for (int f0 = 0; f0 < leup; f0++)
    {
          complex<double> fog_up=complex<double>(0,0),fog_down=complex<double>(0,0);
           //cout<< f0<<"      "<<ii <<endl;
           
            for (int nn0 = 0; nn0 < le0; nn0++)
            {
                int vup= int(nn0);
                int nup1=nup;
                int ndown1=ndown;
                //============================================================//
                //============================================================//
                pair<complex<double>, complex<double>>fog=change_SX(ii,vup,f0);
                fog_up+=fog.first;
                fog_down+=fog.second;
                //============================================================//
                //============================================================//
                nup=nup1;
                ndown= ndown1;
                //cout<< f0<<"      "<<ii <<"     "<<nn0<< "      "<<fog<<endl;
                //cout<< nn0<<endl;
                //=======================================================//
            }

         file<< f0 << "      "<<ii<< "      "<<fog_up<< "      "<<fog_down<< "      "<<es_up(f0)-es_0<<endl;
         //cout<< f0 << "      "<<ii<< "      "<<fog<< "      "<<es_up(f0)-es_0<<endl;
        file<< "    " <<endl;
        //cout<< "    " <<endl;
    }
    
   //file.close();
}
//========================================================//

#endif
