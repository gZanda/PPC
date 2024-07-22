#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char** argv){
	int size, rank, rc;
	MPI_Init(&argc,&argv); // INIT -> argc = número de argumentos, argv = argumentos
	MPI_Comm_size (MPI_COMM_WORLD, &size);	// Get Number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 	// Get Process ID
	cout << "Sou o processo " << rank << " de um total de " << size << " processos" << endl;
	MPI_Finalize();
	return 0;

}
