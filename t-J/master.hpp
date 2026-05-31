#ifndef MASTER_HPP_INCLUDED
#define MASTER_HPP_INCLUDED
#include <iomanip>
#include <fstream>
#include <filesystem>

#include <Eigen/Dense>
#include <highfive/H5File.hpp>
#include <highfive/eigen.hpp>

#include "values.hpp"
#include "Hamiltonian/Hamiltonian.hpp"
#include "Hamiltonian/hopping.hpp"
#include "input/input.hpp"
#include "input/pob.hpp"
#include "input/print.hpp"
#include "matworks.hpp"
#include "Operator_NSC/operatorcall.hpp"
//#include "Operator_SC/operatorcall.hpp"

using namespace std;
using namespace Eigen;
void input::Master_print(int ii,int order)
{
     auto start =chrono::steady_clock::now();
    cout<< "======================================================" <<endl; 
    cout<< "length of the interaction: "<< longrange <<endl;
    cout<< "======================================================" <<endl; 

    operators_NSC Oi;
    Oi.J1=J1;
    Oi.J2=J2;
    Oi.t1=t1;
    Oi.t2=t2;
    Oi.JJ=JJ;
    Oi.tt=tt;
    Oi.longrange=longrange;
    Oi.N=N;
    Oi.nup=nup;
    Oi.ndown=ndown;
    Oi.argument=argument;
   
    //=============================================================================================================================================//
    //=============================================================================================================================================//
    char title0[50];
    char title00[50];

    char title1[50];
    char title2[50];

    char title11[50];
    char title22[50];

    char basis0[50];
    char basis1[50];
    char basis2[50];
    //----------------------------------------------------------------------------------------------------------------------------------------------
    int tut0=int(t1*100);                         //| ==== File | F
    int tut1=int(t2*100);
    int tut2=int(J1*100);                         //| ==== File | F
    int tut3=int(J2*100);
    //----------------------------------------------------------------------------------------------------------------------------------------------
    //bool path= createDirectory("../Data");
    bool path= createDirectory("../Data/EV");
    //----------------------------------------------------------------------------------------------------------------------------------------------
    //=========================================================//
    // Main sector
    //=========================================================//
    std::string h5_0 =
        "../Data/EV/EigenSpectrum_" +
        std::to_string(tut0) + "_" +
        std::to_string(tut1) + "_" +
        std::to_string(tut2) + "_" +
        std::to_string(tut3) + "_" +
        std::to_string(N)    + "_" +
        std::to_string(nup)  + "_" +
        std::to_string(ndown)+ ".h5";

    std::string basis_0 =
        "../Data/EV/Basis_" +
        std::to_string(tut0) + "_" +
        std::to_string(tut1) + "_" +
        std::to_string(tut2) + "_" +
        std::to_string(tut3) + "_" +
        std::to_string(N)    + "_" +
        std::to_string(nup)  + "_" +
        std::to_string(ndown)+ ".dat";


    //=========================================================//
    // nup+1 , ndown-1 sector
    //=========================================================//
    std::string h5_up =
        "../Data/EV/EigenSpectrum_" +
        std::to_string(tut0) + "_" +
        std::to_string(tut1) + "_" +
        std::to_string(tut2) + "_" +
        std::to_string(tut3) + "_" +
        std::to_string(N)    + "_" +
        std::to_string(nup+1)  + "_" +
        std::to_string(ndown-1)+ ".h5";

    std::string basis_up =
        "../Data/EV/Basis_" +
        std::to_string(tut0) + "_" +
        std::to_string(tut1) + "_" +
        std::to_string(tut2) + "_" +
        std::to_string(tut3) + "_" +
        std::to_string(N)    + "_" +
        std::to_string(nup+1)  + "_" +
        std::to_string(ndown-1)+ ".dat";


    //=========================================================//
    // nup-1 , ndown+1 sector
    //=========================================================//
    std::string h5_down =
        "../Data/EV/EigenSpectrum_" +
        std::to_string(tut0) + "_" +
        std::to_string(tut1) + "_" +
        std::to_string(tut2) + "_" +
        std::to_string(tut3) + "_" +
        std::to_string(N)    + "_" +
        std::to_string(nup-1)  + "_" +
        std::to_string(ndown+1)+ ".h5";

    std::string basis_down =
        "../Data/EV/Basis_" +
        std::to_string(tut0) + "_" +
        std::to_string(tut1) + "_" +
        std::to_string(tut2) + "_" +
        std::to_string(tut3) + "_" +
        std::to_string(N)    + "_" +
        std::to_string(nup-1)  + "_" +
        std::to_string(ndown+1)+ ".dat";
    //============================================================//
    //============================================================//
  
    //=========================================================//
    //=========================================================/
    Basis();
    Values();
    //--------------------------------------------------//
    cout<< "======================================================" <<endl; 
    cout<<"J: \n" <<JJ <<"\n"<<endl;
    cout<< "======================================================" <<endl; 
    cout<<"t: \n" <<tt <<"\n"<<endl;
    cout<< "======================================================" <<endl; 
    cout<<"n_up:  "<<nup <<endl;
    cout<<"n_down:  "<<ndown <<endl;
    cout<<"Hilbertspace dimention:  "<<le<<"\n"<<endl;
    cout<< "======================================================" <<endl; 
    BASIS_print();
    //--------------------------------------------------//
    //==========================================================//
    // Try loading existing eigenspectrum
    //==========================================================//
    pair<MatrixXcd, VectorXd> e;
    bool loaded_from_file = false;

    //=========================================================//
    // Read eigenspectrum if available
    //=========================================================//
    //if(ii==0 && std::filesystem::exists(h5_0))
    if(ii==0 && std::ifstream(h5_0).good())
    {
        try
        {
            cout<<"=================================="<<endl;
            cout<<"Loading eigenspectrum from HDF5"<<endl;
            cout<<"=================================="<<endl;

            HighFive::File file(h5_0,HighFive::File::ReadOnly);

            file.getDataSet("eigenvalues").read(e.second);

            file.getDataSet("eigenvectors").read(e.first);

            loaded_from_file = true;

            cout<<"HDF5 read successful"<<endl;
        }
        catch(const std::exception& ex)
        {
            cerr<<"HDF5 Read Error : " <<ex.what()<<endl;

            cerr<<"Recomputing..."<<endl;
        }
    }
    //=========================================================//
    // Diagonalize if file absent
    //=========================================================//
    if(!loaded_from_file)
    {
        Hamiltonian();

        cout<<"=================================="<<endl;
        cout<<"Diagonalizing Hamiltonian"<<endl;
        cout<<"=================================="<<endl;

        e = Eigenspectrum(H0);

        if(ii==0)
        {
            try
            {
                HighFive::File file(h5_0, HighFive::File::Overwrite);

                file.createDataSet( "eigenvalues", e.second);

                file.createDataSet("eigenvectors", e.first);

                cout<<"HDF5 write successful"<<endl;
            }
            catch(const std::exception& ex)
            {
                cerr<<"HDF5 Write Error : "
                    <<ex.what()<<endl;
            }

            //--------------------------------------------------
            // Save basis separately
            //--------------------------------------------------
            std::ofstream bout(basis_0);

            for(long long i=0;
                i<(long long)basisarray.size();
                i++)
            {
                bout << basisarray[i] << "\n";
            }

            bout.close();
        }
    }
    //==========================================================//
    //==========================================================//
    Oi.es_0       = e.second(0);
    Oi.evs_0      = e.first.col(0);
    Oi.basisarray0 = basisarray;
    Oi.le0        = le;
    //==========================================================//
    //==========================================================//

    //------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------

    // nup=nup+1;
    // ndown=ndown-1;
    // Basis();
    // Values();
    // //--------------------------------------------------//
    // cout<< "======================================================" <<endl; 
    // cout<<"n_up:  "<<nup <<endl;
    // cout<<"n_down:  "<<ndown <<endl;
    // cout<<"Hilbertspace dimention: "<<le<<"\n"<<endl;
    // cout<< "======================================================" <<endl; 
    // //--------------------------------------------------//
    // Hamiltonian();
    // //--------------------------------------------------//
    // // cout<< H0 <<endl;
    // //--------------------------------------------------//
    // e = Eigenspectrum(H0);
    // Oi.es_up=e.second;
    // Oi.evs_up=e.first;
    // Oi.basisarray_up=basisarray;
    // //==========================//
    // basisarray.clear();
    // H0.resize(0, 0);
    // //==========================//
    // Oi.leup=le;
    // //------------------------------------------------------------------------------------------------------------------------------------------
    // //------------------------------------------------------------------------------------------------------------------------------------------

    // //============================================================//
    // if(ii==0)
    // {
    //     //=========================================================//
    //     std::ofstream file11;               //| ==== File | eigen 
    //     file11.open(title11);               //| ==== Open | vector

    //     std::ofstream file1;                //| ==== File | eigen
    //     file1.open(title1);                 //| ==== Open | values

    //     std::ofstream bes1;                //| ==== File | basis
    //     bes1.open(basis1);                 //| ==== Open | location
    //     //----------------------------------------------------------//
    //     file11 << std::fixed << std::setprecision(16);
    //     file1 << std::fixed << std::setprecision(16);
    //     bes1 << std::fixed << std::setprecision(16);
    //     //=========================================================//
    //     //=========================================================//
    //     file1<<e.second<<endl;
    //     for (int i = 0; i < e.second.size(); i++)
    //     {
    //        file11<<e.first.col(i)<<endl;
    //        file11<<"    "<<endl;
    //        bes1<<basisarray[i]<<endl;
    //     }
    //     //=========================================================//
    //     file11.close();
    //     file1.close();
    //     bes1.close();
    //     //=========================================================//
    // }
    // //============================================================//
    // //==========================//
    // e.second.resize(0);
    // e.first.resize(0,0);
    // //==========================//

    // //------------------------------------------------------------------------------------------------------------------------------------------
    // //------------------------------------------------------------------------------------------------------------------------------------------

    // nup=nup-2;
    // ndown=ndown+2;
    // Basis();
    // Values();
    // //--------------------------------------------------//
    // cout<< "======================================================" <<endl; 
    // cout<<"n_up:  "<<nup <<endl;
    // cout<<"n_down:  "<<ndown <<endl;
    // cout<<"Hilbertspace dimention: "<<le<<"\n"<<endl;
    // cout<< "======================================================" <<endl; 
    // //--------------------------------------------------//
    // Hamiltonian();
    // //--------------------------------------------------//
    // // cout<< H0 <<endl;
    // //--------------------------------------------------//
    // e = Eigenspectrum(H0);
    // Oi.es_down=e.second;
    // Oi.evs_down=e.first;
    // Oi.basisarray_down=basisarray;
    // //==========================//
    // basisarray.clear();
    // H0.resize(0, 0);
    // //==========================//
    // Oi.ledown=le;
    // //------------------------------------------------------------------------------------------------------------------------------------------
    // //------------------------------------------------------------------------------------------------------------------------------------------

    // //============================================================//
    // if(ii==0)
    // {
    //     //=========================================================//
    //     std::ofstream file22;               //| ==== File | eigen 
    //     file22.open(title22);               //| ==== Open | vector

    //     std::ofstream file2;                //| ==== File | eigen
    //     file2.open(title2);                 //| ==== Open | values

    //     std::ofstream bes2;                //| ==== File | basis
    //     bes2.open(basis2);                 //| ==== Open | location
    //     //----------------------------------------------------------//
    //     file22 << std::fixed << std::setprecision(16);
    //     file2 << std::fixed << std::setprecision(16);
    //     bes2 << std::fixed << std::setprecision(16);
    //     //=========================================================//
    //     //=========================================================//
    //     file2<<e.second<<endl;
    //     for (int i = 0; i < e.second.size(); i++)
    //     {
    //        file22<<e.first.col(i)<<endl;
    //        file22<<"    "<<endl;
    //        bes2<<basisarray[i]<<endl;
    //     }
    //     //=========================================================//
    //     file22.close();
    //     file2.close();
    //     bes2.close();
    //     //=========================================================//
    // }
    // //============================================================//

    // //==========================//
    // e.second.resize(0);
    // e.first.resize(0,0);
    // //==========================//

    // //------------------------------------------------------------------------------------------------------------------------------------------
    // //------------------------------------------------------------------------------------------------------------------------------------------
    Oi.JJ=JJ;
    Oi.tt=tt;
    Oi.output(ii,order);
    //------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------
    cout<< "======================================================" <<endl; 
    auto end =chrono::steady_clock::now();
    auto diff=end-start;
    cout<<"Time for single point calculation calculation:  "<< chrono::duration <double,milli>(diff).count()<<"   "<<endl;
    cout<< "======================================================" <<endl; 

    //------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------
}


#endif