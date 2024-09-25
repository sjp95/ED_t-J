#!/bin/bash
sub=job.sge
#module load gcc-7.5.0
#module load compilers/gcc/9.2.0
#=============================================================================#
#=============================================================================#
g++ -std=c++11 U_O.cpp -o h -llapack -I /usr/include/lapacke \-L /usr/lib64
# for t0 in 100 
#  do
#   for t1 in 10 20 30 40 50
#     do
    for A in 2
     do
      for kpp in {0..11}
       do
          #====================================================================
          echo "#PBS  -N  RIXS_t-J"$kpp"_"$A                   > $sub
          echo "#PBS -l nodes=1:ppn=1"                        >> $sub
          echo "#PBS -j oe "                                  >> $sub
          echo "#PBS -o out.log"                              >> $sub
          echo "#PBS -e err.log"                              >> $sub
          echo "cd"    \$PBS_O_WORKDIR                        >> $sub
          echo "date"                                         >> $sub
          echo "./h $kpp 12 5 5 $A"                           >> $sub
          echo "date"                                         >> $sub
          #====================================================================
          chmod 777 job.sge
          qsub  job.sge
       done
     done
  #   done
  # done
  #./h $A $kpp $t0 $t1
#=============================================================================#
#=============================================================================#
