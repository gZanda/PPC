
#include <stdio.h>
#include <assert.h>

#define N 4

int main(){
    // Define as matrizes quadradas NxN
    int h_a[N][N], h_b[N][N], h_c[N][N];

    // Preenche as matrizes
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            h_a[i][j] = h_b[i][j] = i+j;
            h_c[i][j] = 0;
        }
    }

    // Copia as matrizes h_a e h_b para o dispositivo e paraleliza a soma das matrizes
    #pragma acc data copyin(h_a, h_b) copyout(h_c)
    {
        #pragma acc parallel loop collapse(2)
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                h_c[i][j] = h_a[i][j] + h_b[i][j];
            }
        }
    }

    // Testa se a soma foi executada corretamente
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            assert(h_a[i][j] + h_b[i][j] == h_c[i][j]);
        }
    }

    printf("\nSOMA EXECUTADA COM SUCESSO!\n\n");
}