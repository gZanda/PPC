#include <iostream>
#include <vector>
#include <omp.h>

int findMinMultipleOfTwo(const std::vector<int>& array) {
    int minMultiple = -1;
    #pragma omp parallel for schedule(dynamic, 5) num_threads(4)
    for (int i = 0; i < array.size(); ++i) {
        if (array[i] % 2 == 0) {
            #pragma omp critical
            {
                if (minMultiple == -1 || array[i] < minMultiple) {
                    minMultiple = array[i];
                }
            }
        }
    }
    return minMultiple;
}

int main() {
    int N;
    std::cout << "Informe o tamanho do vetor: ";
    std::cin >> N;

    std::vector<int> vetor(N);
    std::cout << "Informe os elementos do vetor:\n";
    for (int i = 0; i < N; ++i) {
        std::cin >> vetor[i];
    }

    int menorMultiploDeDois = findMinMultipleOfTwo(vetor);

    if (menorMultiploDeDois != -1) {
        std::cout << "O menor múltiplo de 2 no vetor é: " << menorMultiploDeDois << std::endl;
    } else {
        std::cout << "Não há múltiplos de 2 no vetor." << std::endl;
    }

    return 0;
}
