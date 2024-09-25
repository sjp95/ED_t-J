#ifndef POBOPPSC_HPP_INCLUDED
#define POBOPPSC_HPP_INCLUDED
#include <math.h>
#include <complex>
#include <Eigen/Dense>
#include <vector>
#include <omp.h>
#include "operators.hpp"
using namespace std;
using namespace Eigen;
//================================================================================//
//================================================================================//

//=========================================================//
//=========================================================//
long long operators_SC::fact(long long n)
{
  if (n == 0 || n == 1)
  return 1;
  else
  return n * fact(n - 1);
}
//=========================================================//
long long operators_SC:: nCr(long long n,long long r)
{
  if(n>=r)
  {
      return fact(n) / (fact(r) * fact(n - r));
  }
  else
  {
      return 0;
  }
}
//=========================================================//
//=========================================================//


//================================================================================//
                                   //== POB for Up ==//
//================================================================================//


//==============================================//
                //== POB number ==//
//==============================================//
void operators_SC::pob_up_n(int value)
{
    int j=N;
    int temp= value;
    upi=VectorXi ::Zero(N);
    
    for(int k=nup;k>=1;k-=1)
    {
      //==========step-1==========//
        do      
        {
          j=j-1;
          int p= nCr(j,k);
          
          if (temp>=p)
          {
            temp = temp-p;
            upi(j) = 1;
          }
          else
          {
            upi(j)=0;
          }

        } while (j>0 && upi(j)!=1);
    }
    //==========step-2==========//
    if (j >= 0)
    for(int k=j-1;k>=0;k=k-1)
    {
      upi(k)=0;
    }
    //===========================//
  //return upi;
}
//=========================================================//
//=========================================================//

//=================================================================================//
//=================================================================================//

//==============================================//
                //== POB values ==//
//==============================================//
int operators_SC::pob_up_v()
{
  int V=0;
  for(int i=0;i<upi.size();i++)
  {
    int alp=0;
    if(upi(i)>0)
    {
      for (int j = 0; j <=i; j++)
      {
        alp+=upi(j);
      }
      V+=upi(i)*nCr(i,alp);
    }
  }

  return V;
}
//=========================================================//
//=========================================================//



//================================================================================//
                                //== POB for down ==//
//================================================================================//



//==============================================//
                //== POB number ==//
//==============================================//
void operators_SC::pob_down_n(int value)
{
    int j=N;
    int temp= value;
    downi=VectorXi ::Zero(N);
    
    for(int k=ndown;k>=1;k-=1)
    {
      //==========step-1==========//
        do      
        {
          j=j-1;
          int p= nCr(j,k);
          
          if (temp>=p)
          {
            temp = temp-p;
            downi(j) = 1;
          }
          else
          {
            downi(j)=0;
          }

        } while (j>0 && downi(j)!=1);
    }
    //==========step-2==========//
    if (j >= 0)
    for(int k=j-1;k>=0;k=k-1)
    {
      downi(k)=0;
    }
    //===========================//
  //return downi;
}
//=========================================================//
//=========================================================//




//==============================================//
                //== POB values ==//
//==============================================//
int operators_SC:: pob_down_v()
{
  int V=0;
  for(int i=0;i<downi.size();i++)
  {
    int alp=0;
    if(downi(i)>0)
    {
      for (int j = 0; j <=i; j++)
      {
        alp+=downi(j);
      }
      V+=downi(i)*nCr(i,alp);
    }
  }

  return V;
}
//=========================================================//
//=========================================================//


//=========================================================================//
            //====An algorithm to find location of a number====//
//=========================================================================//
int operators_SC::find0(int target) 
{
    int left = 0;
    int right = basisarray0.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (basisarray0[mid] == target) 
        {
            return mid; // Number found at index mid
        } 
        else if (basisarray0[mid] < target) 
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
//=========================================================================//
// int operators_SC::find_up(int target) 
// {
//     int left = 0;
//     int right = basisarray_up.size() - 1;

//     while (left <= right)
//     {
//         int mid = left + (right - left) / 2;

//         if (basisarray_up[mid] == target) 
//         {
//             return mid; // Number found at index mid
//         } 
//         else if (basisarray_up[mid] < target) 
//         {
//             left = mid + 1; // Search the right half
//         } 
//         else 
//         {
//             right = mid - 1; // Search the left half
//         }
//     }
//     return -1; // Number not found in the array
// }
// //=========================================================================//
// //=========================================================================//
// int operators_SC::find_down(int target) 
// {
//     int left = 0;
//     int right = basisarray_down.size() - 1;

//     while (left <= right)
//     {
//         int mid = left + (right - left) / 2;

//         if (basisarray_down[mid] == target) 
//         {
//             return mid; // Number found at index mid
//         } 
//         else if (basisarray_down[mid] < target) 
//         {
//             left = mid + 1; // Search the right half
//         } 
//         else 
//         {
//             right = mid - 1; // Search the left half
//         }
//     }
//     return -1; // Number not found in the array
// }
//=========================================================================//

//=========================================================================//
            //====00000000000000 Nested Class 00000000000000====//
//=========================================================================//


//================================================================================//
//================================================================================//
#endif
