#!/bin/bash
sub=job.sge
#module load gcc-7.5.0
#module load compilers/gcc/9.2.0
#=============================================================================#
#=============================================================================#
# g++ -std=c++11 U_O.cpp -o h -llapack -llapacke

# ./h 0 6 3 3 0 &

# ./h 0 6 2 4 0 &
# ./h 0 6 4 2 0 &

# ./h 0 6 1 5 0 &
# ./h 0 6 5 1 0 &

# ./h 0 6 0 6 0 &
# ./h 0 6 6 0 0 &



#!/bin/bash
set -e

# Initialize oneAPI environment for runtime libraries
if [ -f "/opt/intel/oneapi/setvars.sh" ]; then
    source /opt/intel/oneapi/setvars.sh --force
fi

# Performance tuning: Use all physical cores
export MKL_NUM_THREADS=$(nproc)
export OMP_NUM_THREADS=2 #$(nproc)

# Force Eigen to use MKL backend (if s3.cpp includes Eigen)
export EIGEN_USE_MKL_ALL=1

mkdir -p build

cmake -S . -B build
cmake --build build -j$(nproc)

echo "Starting execution with $MKL_NUM_THREADS threads..."
   
# for hz in {0..150..2} #$(seq 1.02 0.02 1.50) 
# do
#  for Jz in 100.0 #$(seq 1.0 -0.02 0.0)
#  do
  ./build/s1 0 6 3 3 0 &
#  done
# done
