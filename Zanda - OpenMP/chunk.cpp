#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    
    cout << "Qual o tamanho do vetor: ";
    int N;
    cin >> N;

    cout << "Informe os elementos do vetor: " << endl;
    int vetor[N];
    for (int i = 0; i < N; i++){
        cin >> vetor[i];
    }

    int menor = -1;

    #pragma omp parallel for schedule(dynamic, 5) num_threads(4) shared(vetor, menor)
    for (int i = 0; i < N; ++i) {
        if (vetor[i] % 2 == 0) {
            #pragma omp critical
            {
                if (menor == -1 or vetor[i] < menor) {
                    menor = vetor[i];
                }
            }
        }
    }

    if (menor != -1) {
    cout << "O menor múltiplo de 2 no vetor é: " << menor << endl;
    } else {
        cout << "Não há múltiplos de 2 no vetor." << endl;
    }

    return 0;
}
