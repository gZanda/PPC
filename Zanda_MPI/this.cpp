#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 16 // Tamanho do vetor

int main(int argc, char *argv[]) {
    int id_process, n_process;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_process);
    MPI_Comm_size(MPI_COMM_WORLD, &n_process);

    int data[N] = {0};
    int subset_size = N / n_process;
    int subset[subset_size];
    int min_value = INT_MAX;

    if (id_process == 0) {
        // Processo 0 gera um vetor de valores aleatórios
        srand(time(NULL));
        std::cout << "Vetor original:\n";
        for (int i = 0; i < N; i++) {
            data[i] = rand() % 100;
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Processo 0 distribui subconjunto de valores para os demais processos - SCATTER
    MPI_Scatter(data, subset_size, MPI_INT, subset, subset_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo calcula o valor mínimo do seu subconjunto de valores
    for (int i = 0; i < subset_size; i++) {
        if (subset[i] < min_value) {
            min_value = subset[i];
        }
    }

    // Processo 1 recebe o valor mínimo de cada subconjunto, calcula o mínimo do conjunto total e imprime na tela - GATHER
    int global_min;
    if (id_process == 1) {
        int mins[n_process];
        MPI_Gather(&min_value, 1, MPI_INT, mins, 1, MPI_INT, 1, MPI_COMM_WORLD);
        global_min = mins[0];
        for (int i = 1; i < n_process; i++) {
            if (mins[i] < global_min) {
                global_min = mins[i];
            }
        }
        std::cout << std::endl << "Valor mínimo do conjunto total: " << global_min << std::endl;
    } else {
        MPI_Gather(&min_value, 1, MPI_INT, NULL, 0, MPI_INT, 1, MPI_COMM_WORLD);
    }

    // Processo 1 envia o valor mínimo para todos os outros processos - BROADCAST
    MPI_Bcast(&global_min, 1, MPI_INT, 1, MPI_COMM_WORLD);

    // Cada processo deve multiplicar cada elemento do seu subconjunto pelo valor mínimo
    for (int i = 0; i < subset_size; i++) {
        subset[i] *= global_min;
    }

    // Cada processo envia seu conjunto de valores alterados para o processo 0 - GATHER
    MPI_Gather(subset, subset_size, MPI_INT, data, subset_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Processo 0 imprime o vetor resultante na tela
    if (id_process == 0) {
        std::cout << std::endl << "Vetor resultante: " << std::endl;
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
