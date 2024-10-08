#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define NX 100

int main(void)
{
    double vecA[NX], vecB[NX], vecC[NX];
    double sum;
    int i;

    for (i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }

    for (i = 0; i < NX; i++) {
       vecC[i] = vecA[i] + vecB[i];
    } 

    sum = 0.0;
    
    printf("Vetor = ");
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
        printf(" %.2f", vecC[i]);
    }
    printf("\nTotal: %18.16f\n", sum);

    return 0;
}