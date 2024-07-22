// Bibliotecas utilizadas
#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char** argv) {
	// declaracao das variaveis locais
	int my_rank; /* identificador do processo*/
	int p; /* número de processos */
	int buffer; /* dado recebido */
	int tag = 0; /* tag para mensagens*/
	MPI_Status status; /* retorna de estado do receive */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	// ( variable with the data to be sent, number of elements to be sent, data type, ID of who receives the message, TAG of the message, MPI_COMM_WORLD )
	MPI_Send(&my_rank, 1, MPI_INT, p-1-my_rank, tag, MPI_COMM_WORLD);
	// ( variable that will receive data, number of elements to be received, data type, ID of who sents the message, TAG of the message, MPI_COMM_WORLD, return status )
	MPI_Recv(&buffer, 1, MPI_INT, p-1-my_rank, tag, MPI_COMM_WORLD, &status);
	cout << "Meu rank:" << my_rank << ". Recebi mensagem do proc "<<  buffer<< endl;
	MPI_Finalize();
	return(0);
}

