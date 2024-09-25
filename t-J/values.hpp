#ifndef VALUES_HPP_INCLUDED
#define VALUES_HPP_INCLUDED
#include <math.h>
#include "input/input.hpp"
#include "input/pob.hpp"
#include <Eigen/Dense>

#include <complex>
using namespace Eigen;
using namespace std;

//=================== General input ====================//
void input:: Values()
{
    int D=1;
   
    if(D==1)
    {  
        JJ=MatrixXd ::Zero(N,N);
        tt=MatrixXd ::Zero(N,N);
        for(int i=0;i<N;i+=3)
        {
            if(i%3==0)
            {
                //==============// i
                //==============// i+1
                 if (i+1<N)
                {
                    tt(i,(i+1)%N)=t1;
                    tt((i+1)%N,i)=t1;

                    JJ(i,(i+1)%N)=J1;
                    JJ((i+1)%N,i)=J1;
                }
                //==============// i+1
                //==============// i+2
                if (i+1<N && i+2<N)
                {
                    tt(i+1,i+2)=t1;
                    tt(i+2,i+1)=t1;

                    JJ(i+1,i+2)=J1;
                    JJ(i+2,i+1)=J1;
                }
                //==============// i+1
                //==============// i+3
                // if (i+3<N)
                // {
                   tt(i+2,(i+3)%N)=t2;
                   tt((i+3)%N,i+2)=t2;

                   JJ(i+2,(i+3)%N)=J2;
                   JJ((i+3)%N,i+2)=J2;
                // }
                //==============//
                //==============// 
            }
            
        
        }
    }
    if(D==2)
    {
        JJ=MatrixXd ::Zero(N,N);
        tt=MatrixXd ::Zero(N,N);
        for(int i=0;i<N;i+=1)
        {
            //==============// i
            //==============// i+1
            tt(i,(i+1)%N)=t1;
            tt((i+1)%N,i)=t1;

            JJ(i,(i+1)%N)=J1;
            JJ((i+1)%N,i)=J1;
        }
    }

}
//======================================================//
//======================================================//
void input::Basis()
{
    le = nCr(N,nup)*nCr(N-nup,ndown);
    H0 = MatrixXcd :: Zero(le,le);
    JJ=MatrixXd ::Zero(N,N);
    tt=MatrixXd ::Zero(N,N);

    upi=VectorXi ::Zero(N);
    downi=VectorXi ::Zero(N);

    for (int i=0;i<nCr(N,nup)*nCr(N,ndown);i++)
    {
        int x= nCr(N,nup);
        int vup= int(i%x);
        int vdown=int(i/x);

        pob_up_n(vup);
        pob_down_n(vdown);
        
        int flag=0;
        
        for ( int n =0; n<N; n++)
        {
            if(upi(n)==1 && downi(n)==1)
            {
              flag++;
              break;
            }
        }
        if(flag==0)
        {
            basisarray.push_back(i);
            //cout<< i <<endl;
        }
    }
    //cout<<"\n" <<basisarray.size()<<"     "<< le<<" "<<nup<<" "<<ndown <<endl;
    // evs = MatrixXcd :: Zero(le,le);      //             | A
    // es = VectorXd :: Zero(le);
}

//=========================================================================//
            //====An algorithm to find location of a number====//
//=========================================================================//
int input::find(int target) 
{
    int left = 0;
    int right = basisarray.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (basisarray[mid] == target) 
        {
            return mid; // Number found at index mid
        } 
        else if (basisarray[mid] < target) 
        {
            left = mid + 1; // Search the right half
        } 
        else 
        {
            right = mid - 1; // Search the left half
        }
    }
    return -1; // Number not found in the array
}
//=========================================================================//
            //====00000000000000 Nested Class 00000000000000====//
//=========================================================================//


#endif
