Homework 2 Parallel and Scientific Computing
============================================

## Part 1
To compile Part 1 run the following command...
`mpicc hello_world_mpi.c -o hello_world`
Run the binary with the following command
`mpirun -n 4 ./hello_world`
You can change the number to run with a different set of processes!


## Part 2
To compile Part 2 run the following command...
`mpicc collective_mpi.c -o collective_mpi`
Run the binary with the following command
`mpirun -n 4 ./collective_mpi`
This program expects to run with 4 processes. This is because of Scatter.

## Part 3
To compile Part 3 run the following command...
`mpicc pi_mpi.c -o pi_mpi`
Run the binary with the provided bash script.
run.sh will run the command for 2 to 20 cores and print it in a CSV format.
`./run.sh`
You may have to change the script to be executable by your user. 
You can also run the binary in the same way you did the others!
