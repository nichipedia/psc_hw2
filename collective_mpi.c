#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int data;
    int recv;
    int nums[12];
    int subs[3];
    int *psubs = &subs[0];
    int *pnums = &nums[0];
    int sum = 0;
    int prod = 1;
    int sums[4];
    float mean = 0;
    int sumTotal = 0;
    int prodTotal = 0;
    int max;
    int min;

    printf("Process %d will wait on others!\n", rank);
    MPI_Barrier(MPI_COMM_WORLD); // Example of Barrier communication 4
    printf("Hello World from MPI Process: %d\n", rank);
    if (rank == 0) {
        data = 400;
        int i;
        for (i = 0; i < 12; i++) {
            nums[i] = i+1;
        }
    }
    MPI_Bcast(&data, world_size, MPI_INT, 0, MPI_COMM_WORLD); // Example of Bcast Communication 0
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(pnums, 3, MPI_INT, psubs, 3, MPI_INT, 0, MPI_COMM_WORLD); //Example of Scatter Communication 1
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank != 0) {
        printf("Process %d recieved %d\n", rank, data);
    }
    int i;
    for (i = 0; i < 3; i++) {
        sum += subs[i];   
        prod *= subs[i];
    }
    //printf("Scatter sent to process %d: %d\n", rank, subs[0]);
    MPI_Gather(&sum, 1, MPI_INT, &sums, 1, MPI_INT, 0, MPI_COMM_WORLD); //Example Gather Communication 2
    if (rank == 0) {
        for (i = 0; i < 4; i++) {
            mean += sums[i];
        }
        mean /= 12;
        printf("Mean of SUM(12) using scatter/gather: %f\n", mean);
        mean = 0;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&sum, &sumTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); //Example of Reduce for sum
    MPI_Reduce(&prod, &prodTotal, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD); // Example of Reduce for prod

    if (rank == 0) {
        printf("SUM(12) using Reduce: %d\n", sumTotal);   
        printf("PROD(12) using Reduce: %d\n", prodTotal);   
    }


    MPI_Finalize();
}
