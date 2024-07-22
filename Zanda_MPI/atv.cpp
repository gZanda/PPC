#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100  // Tamanho do vetor

void generate_random_vector(int *vector, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 299 + 2;  // Valores aleatórios entre 2 e 300
    }
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int vector[N];
    int local_min, global_min;
    int local_size = N / size;
    int *local_vector = (int*) malloc(local_size * sizeof(int));

    if (rank == 0) {
        generate_random_vector(vector, N);
        printf("Vetor gerado pelo processo 0:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", vector[i]);
        }
        printf("\n");

        MPI_Scatter(vector, local_size, MPI_INT, local_vector, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(NULL, local_size, MPI_INT, local_vector, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Cada processo calcula o valor mínimo do seu subconjunto
    local_min = local_vector[0];
    for (int i = 1; i < local_size; i++) {
        if (local_vector[i] < local_min) {
            local_min = local_vector[i];
        }
    }

    // O processo 1 recebe os valores mínimos de cada processo
    if (rank == 1) {
        int *mins = (int*) malloc(size * sizeof(int));
        MPI_Gather(&local_min, 1, MPI_INT, mins, 1, MPI_INT, 1, MPI_COMM_WORLD);
        global_min = mins[0];
        for (int i = 1; i < size; i++) {
            if (mins[i] < global_min) {
                global_min = mins[i];
            }
        }
        printf("Valor mínimo do conjunto total: %d\n", global_min);
        free(mins);
    } else {
        MPI_Gather(&local_min, 1, MPI_INT, NULL, 1, MPI_INT, 1, MPI_COMM_WORLD);
    }

    // Processo 1 envia o valor mínimo para todos os outros processos
    MPI_Bcast(&global_min, 1, MPI_INT, 1, MPI_COMM_WORLD);

    // Cada processo multiplica cada elemento do seu subconjunto pelo valor mínimo
    for (int i = 0; i < local_size; i++) {
        local_vector[i] *= global_min;
    }

    // Cada processo envia o seu subconjunto alterado para o processo 0
    if (rank == 0) {
        MPI_Gather(MPI_IN_PLACE, local_size, MPI_INT, vector, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Gather(local_vector, local_size, MPI_INT, NULL, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Processo 0 imprime o vetor resultante
    if (rank == 0) {
        printf("Vetor resultante após multiplicação pelo valor mínimo:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    free(local_vector);
    MPI_Finalize();
    return 0;
}
