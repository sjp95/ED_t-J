#!/bin/bash
sub=job.sge
#module load gcc-7.5.0
#module load compilers/gcc/9.2.0
#=============================================================================#
#=============================================================================#
g++ -std=c++11 U_O.cpp -o h -llapack -llapacke

./h 0 6 3 3 0 &

./h 0 6 2 4 0 &
./h 0 6 4 2 0 &

./h 0 6 1 5 0 &
./h 0 6 5 1 0 &

./h 0 6 0 6 0 &
./h 0 6 6 0 0 &