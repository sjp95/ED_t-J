/*||==================================================================================================||*/
/*||              ****** Calculation of Electron electron interaction strength (U) ******             ||*/
/*||                         ******* vs order parameter (|<Phi>|) *******                             ||*/
/*||                              ******** for Total system ********                                  ||*/
/*||==================================================================================================||*/
#include <iostream>
#include <cmath>
#include <math.h> 
#include <complex>
#include <Eigen/Dense>
#include <fstream>
#include <vector>
#include <omp.h>
using namespace std;
using namespace Eigen;
char title0[100];
char title1[100];
char title2[100];
char title3[100];
#define roun_d(x,d) ((floor(((x)*pow(10,d))+.5))/pow(10,d))

int main(int argc,char* argv[])
{
    double gamma=5.0;
   cout<< "yes" <<endl;

    for (int j = -10; j <= 10; j+=10)
    {
        //---------------------------------------------------//
        sprintf(title0,"Data/Twoc_%d.dat",j);  //| ==== Name | I
        std::ofstream file0;               //| ==== File | L
        file0.open(title0);  
        //---------------------------------------------------//
        
          //==================================================================//
          //==================================================================//
          sprintf(title1,"Data/Twomagnon_%d.dat",j);  //| ==== Name | I
          std::ifstream file1;                             //| ==== File | L
          file1.open(title1);             //| ==== Open | E
          //==================================================================//
          
          vector<double> pi , w , n1 , e1;
          if(file1)
          {
             
              VectorXd cn=VectorXd:: Zero(4);
              while (file1>>cn(0)>>cn(1)>>cn(2)>>cn(3))
              {
                pi.push_back(cn(0));
                w.push_back(cn(1));
                n1.push_back(cn(2));
                e1.push_back(cn(3));
              }  
          }
         
          //==================================================================//
          //==================================================================//
          sprintf(title2,"Data0/Twomagnon_%d.dat",j);  //| ==== Name | I
          std::ifstream file2;                             //| ==== File | L
          file2.open(title2);             //| ==== Open | E
          //==================================================================//
          vector<double>n2 , e2;
          if(file2)
          {
      
              VectorXd cn=VectorXd:: Zero(4);
              while (file2>>cn(0)>>cn(1)>>cn(2)>>cn(3))
              {
                n2.push_back(cn(2));
                e2.push_back(cn(3));
              }  
          }
         
          // //==================================================================//
          // //==================================================================//
          // sprintf(title3,"data0/ThreemagnonN_%d.dat",j);  //| ==== Name | I
          // std::ifstream file3;                             //| ==== File | L
          // file3.open(title3);             //| ==== Open | E
          // //==================================================================//
          // vector<double> n3 , e3;
          // if(file3)
          // {
             
          //     VectorXd cn=VectorXd:: Zero(4);
          //     while (file3>>cn(0)>>cn(1)>>cn(2)>>cn(3))
          //     {
          //       n3.push_back(cn(2));
          //       e3.push_back(cn(3));
          //     }  
          // }
          // //==================================================================//
          // //==================================================================//
            

          for(int i=0;i<w.size();i++)
          {
            file0<< pi[i] <<"     "<< w[i] <<"     "<< n1[i]/pow(gamma,2)+400.0*n2[i]/pow(gamma,4) <<endl;
            // cout<< "yes" << n2[i]<<endl;
          }
          //cout<< "yes" <<endl;
      file0.close(); 
    }
 
 return 0;
}


// Spin_fill=-0.1;
// filling= double((1-0.05)*(Nf-Nf));
// c=2.33;
