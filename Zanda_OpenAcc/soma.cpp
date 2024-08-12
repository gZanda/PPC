#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>

int main() {
    const int N = 100; // Tamanho dos vetores

    // Inicialização dos vetores
    int a[N], b[N], c[N];

    // Preenche os vetores a e b com alguns valores
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = 2 * i;
    }
    printf("Vetor a:\n");
    for (int i = 0; i < 100; ++i) {
        std::cout << "a[" << i << "] = " << a[i] << std::endl;
    }
    printf("Vetor b:\n");
    for (int i = 0; i < 100; ++i) {
        std::cout << "b[" << i << "] = " << b[i] << std::endl;
    }

    // Soma dos vetores a e b em paralelo usando OpenACC
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    // Exibe os primeiros 10 resultados
    printf("Resultado:\n");
    for (int i = 0; i < 100; ++i) {
        std::cout << "c[" << i << "] = " << c[i] << std::endl;
    }

    return 0;
}
