#ifndef SISJSC_HPP_INCLUDED
#define SISJSC_HPP_INCLUDED
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

//========================================================================================================================================//
//========================================================================================================================================//
pair<complex<double>, complex<double>> operators_SC::change_SISJ(int ii,int jj,int nn0,int f0)
{
    complex<double> fog_up1=complex<double>(0,0);
    complex<double> fog_up2=complex<double>(0,0);
    complex<double> fog_down1=complex<double>(0,0);
    complex<double> fog_down2=complex<double>(0,0);
    //===========================//
    int n = basisarray0[nn0];
    int x= nCr(N,nup);
    int vup= int(n%x);
    int vdown=int(n/x);

    int nup1=nup;
    int ndown1=ndown;
    //===========================//
    //===========================//
    pob_up_n(vup);
    pob_down_n(vdown);
    int aupi=upi(ii);
    int adowni=downi(ii);
    double ssz= double((upi(ii)-downi(ii))*(upi(jj)-downi(jj))*0.25);
    //========================================================================================//
    //========================================================================================//
    //cout<< n << "   "<<vup<< "   "<<vdown << "   "<<ssz<<endl;
    //cout<< upi.transpose() << "   "<<downi.transpose()<< "   "<<vdown << "   "<<ssz<<endl;
    //cout<< aupi << "   "<<adowni<<"\n"<<endl;
    //=========================================================================================//
    //========================================================================================//

    //========================================================================================================================================//
    //========================================================================================================================================//
    if(upi(ii)+downi(ii)>0 && abs(ssz)>0)
    {
        //========================================================================================================================================//
        x= nCr(N,nup);
        //=================================================================//
        int q=int(pob_down_v()*x+pob_up_v()); // Reconstruction of the new basis
        q=find0(q);   // finding the new basis location
        //=================================================================//
        fog_down1=conj(evs_0(q,f0))*evs_0(nn0,0)*ssz*JJ(ii,jj)*0.5;                   
        //========================================================================================================================================//
        //========================================================================================================================================//
    }
    //========================================================================================================================================//
    //========================================================================================================================================//



    //========================================================================================================================================//
    //========================================================================================================================================//
    nup=nup1;
    ndown= ndown1;
    //===========================//
    n = basisarray0[nn0];
    x= nCr(N,nup);
    vup= int(n%x);
    vdown=int(n/x);
    //===========================//
    //===========================//
    pob_up_n(vup);
    pob_down_n(vdown);
    int pre0=abs(upi(ii)*downi(jj)+upi(jj)*downi(ii));
    //================================================//
    //================================================//
    
    if(abs(pre0)>0)
    {
        //======================//
        //======================//
        upi(jj)=1-upi(jj);
        downi(jj)=1-downi(jj);
        //======================//
        //======================//
        //========================================================================================================================================//
        x= nCr(N,nup);
        //=================================================================//
        int q=int(pob_down_v()*x+pob_up_v()); // Reconstruction of the new basis
        q=find0(q);   // finding the new basis location
        //=================================================================//
        fog_down2=conj(evs_0(q,f0))*evs_0(nn0,0)*JJ(ii,jj)*0.25;
        // cout<< f0 << "   "<<nn0<< "   "<<fog_down2 << "   "<<ssz<<endl;
        //=================================================================//           
        //========================================================================================================================================//
    
    }
    //========================================================================================================================================//
    //========================================================================================================================================//
    
    //=======================================================//
    return  make_pair(fog_up1+fog_up2,fog_down1+fog_down2);
    //=======================================================//
}


//=====================================================================================================================================================================//
//=====================================================================================================================================================================//

void operators_SC::SiSj(int ii)
{
    //-------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------
    char title0[150];
    //==============================================================================================================================//
    //==============================================================================================================================//
    int tut0=int(t1*100);                        
    int tut1=int(t2*100);
    int tut2=int(J1*100);                
    int tut3=int(J2*100);
    //-------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------
    bool path= createDirectory("../Data");
    path= createDirectory("../Data/SC");
    path= createDirectory("../Data/SC/SXiSiSj");
    sprintf(title0,"../Data/SC/SXiSiSj/SXiSiSj_%d_%d_%d_%d_%lld_%lld_%lld_%d.dat",tut0,tut1,tut2,tut3,N,nup,ndown,ii); //| ==== Name | I
    std::ofstream file;               //| ==== File | L
    file.open(title0);                //| ==== Open | E
    //-------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------
    file << std::fixed << std::setprecision(16);
    //-------------------------------------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------------------------

    //==============================================================================================================================//
    //==============================================================================================================================//

    for (int f0 = 0; f0 < le0; f0++)
    {
          complex<double> fog_up=complex<double>(0,0),fog_down=complex<double>(0,0);
          //cout<< f0<<"      "<<ii <<endl;
          //cout<<" "<<endl;
            //============================================================//
            //============================================================//
            for (int nn0 = 0; nn0 < le0; nn0++)
            {
                int vup= int(nn0);
                int nup1=nup;
                int ndown1=ndown;
                //============================================================//
                //============================================================//
                for (int nei = ii+1; nei <= ii+longrange; nei++)
                {
                    int jj=nei%N; 
                    //============================================================//
                    //============================================================//                            
                    if (abs(JJ(ii,jj))>0)
                    {
                        pair<complex<double>, complex<double>>fog=change_SISJ(ii,jj,vup,f0);
                        fog_up+=fog.first;
                        fog_down+=fog.second;
                    }
                    //============================================================//
                    nup=nup1;
                    ndown= ndown1;
                    //------------------------------------------------------------
                    jj=(ii-(nei-ii)+N)%N;
                    //============================================================//
                    if (abs(JJ(ii,jj))>0)
                    {
                        pair<complex<double>, complex<double>>fog=change_SISJ(ii,jj,vup,f0);
                        fog_up+=fog.first;
                        fog_down+=fog.second;
                    }
                    //============================================================//
                    nup=nup1;
                    ndown= ndown1;
                    //============================================================//
                    //============================================================//
                }
                //============================================================//
                //============================================================//
            }

        file<< f0 << "      "<<ii<< "      "<<fog_up<< "      "<<fog_down<< "      "<<es_0(f0)-es_0(0)<<endl;
        file<< "    " <<endl;
        //cout<< "    " <<endl;
    }
    
   //file.close();
}
//=====================================================================================================================================================================//
//=====================================================================================================================================================================//

#endif
