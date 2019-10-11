#!/bin/bash

echo 'PI,TIME,CORES'
for i in {2..20}
    do
        mpirun -n $i ./pi_mpi
    done
