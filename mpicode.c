#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("MPI process %d I start waiting on the barrier.\n", my_rank);
}
