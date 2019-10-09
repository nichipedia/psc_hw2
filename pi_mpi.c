#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD);
    double x = 0;
    int num_steps = 10000000;
    double sum = 0.0;
    double sumTotal;
    double step = 1.0/(double) num_steps;
    int i;
    int slice = num_steps/world_size;
    double t1 = MPI_Wtime();
    for (i = slice*rank; i < (slice*rank)+(slice-1); i++) {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&sum, &sumTotal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double t2 = MPI_Wtime();
    double speed = t2-t1;
    if (rank == 0) {
        double pi = step*sumTotal;
        printf("%f,%f,%d\n", pi, speed, world_size);
    }
    MPI_Finalize();
}
