#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char** argv){

	int n=0, myid, numprocs;
	MPI_Init(&argc,&argv); // Initialize MPI
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs); // Get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD,&myid); // Get my ID
	if (myid==0){	// Master process sends message
		n=90;
	}
	// ( shared variable, number of elements, ??? , ID of who sends the message, MPI_COMM_WORLD )
	MPI_Bcast(&n, 1, MPI_INT,0, MPI_COMM_WORLD);
	
	cout << "O processo " << myid << " recebeu o valor n=" <<  n << endl;
	MPI_Finalize();
	return 0;
}
