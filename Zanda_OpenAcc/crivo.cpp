#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define N 1000  // Número de elementos da lista

void crivo_array(int *a, int n) {
    int k = 2;

    #pragma acc parallel loop
    for (int idx = 0; idx < n; idx++) {
        a[idx] = idx;
    }

    while (k * 2 <= n) {
        #pragma acc parallel loop
        for (int idx = 0; idx < n; idx++) {
            if ((a[idx] % k == 0) && (a[idx] > 0) && (a[idx] != k)) {
                a[idx] = -a[idx];  // Marcar o elemento na lista
            }
        }

        k++;

        // Achar o próximo número não marcado
        while (k < n && a[k] < 0) {
            k++;
        }
    }
}

int main(void) {
    int *a_h;

    // Alocando espaço na memória da CPU
    a_h = (int*)malloc(N * sizeof(int));

    // Copiando os dados para o dispositivo e realizando o crivo
    #pragma acc data copy(a_h[0:N])
    {
        crivo_array(a_h, N);
    }

    // Imprimindo os números primos entre 2 e N
    printf("São primos os números entre 2 e %d\n", N);
    for (int i = 2; i < N; i++) {
        if (a_h[i] > 0)
            printf("%d\n", a_h[i]);
    }

    free(a_h); // Liberando memória da CPU
    return 0;
}