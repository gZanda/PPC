// Questão: Implemente um programa que gere um vetor N preenchido com valores aleatórios pelo processo pai. Em seguida, o processo pai cria pipe e 2 processos filho. O pai  encontra o maior valor do primeiro 1/3 do vetor e envia 1/3 dos demais elementos para cada  processo filho. Cada filho deverá encontrar o menor valor e devolver o resultado para o pai. O pai encontra o menor valor de sua parte e define qual é o menor valor geral e imprime o resultado.

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <ctime>
using namespace std;

int main()
{

    // Declara vetor
    srand(time(NULL));
    const int N = 12; // Tamanho do vetor
    int vetor[N];

    // Valores aleatórios
    srand(time(NULL));
    for (int i = 0; i < N; ++i)
    {
        vetor[i] = rand() % 100;
        cout << vetor[i] << " ";
    }

    cout << endl;

    // Cria pipe
    int fd[2];
    pipe(fd);
    if (pipe(fd) < 0)
    {
        cout << "Pipe não criado" << endl;
        _exit(0);
    }
    else
    {
        cout << "Pipe criado com sucesso" << endl;
    }

    pid_t pid;

    // Cria 2 processos filho
    for (int i = 0; i < 2; i++) // Loop para criar 2 filhos
    {
        pid = fork(); // Cria processo filho

        // Casos do PID
        if (pid < 0)
        {
            cout << "Fork falhou" << endl;
            _exit(0);
        }
        else if (pid == 0)
        {
            cout << "Processo filho" << endl;
            close(fd[1]);
            int vetorFilho[N / 3];
            // int = 4 bytes
            if (read(fd[0], vetorFilho, (N / 3) * sizeof(int)) == -1) // TEM QUE SER EM BYTES !!!!
            {
                cout << "Erro na leitura do pipe" << endl;
                _exit(0);
            }
            close(fd[0]);

            // Calcular o menor valor do vetorFilho
            int menor = vetorFilho[0];
            for (int i = 1; i < N / 3; i++)
            {
                if (vetorFilho[i] < menor)
                {
                    menor = vetorFilho[i];
                }
            }
            cout << "Menor valor do vetorFilho: " << menor << endl;
        }
        else
        {
            cout << "Processo pai final" << endl;
            wait(NULL);
            cout << "Filho completou" << endl;
        }
    }
    close(fd[0]); // Fecha a leitura do pipe

    // Enviar 1/3 dos elementos para cada filho
    for (int i = 0; i < 2; ++i)
    {
        if (write(fd[1], vetor + (N / 3) * (i + 1), (N / 3) * sizeof(int)) == -1)
        {
            cout << "Erro na escrita do pipe" << endl;
            _exit(0);
        }
    }
    close(fd[1]); // Fecha a escrita do pipe

    // Calcular o menor valor da parte do PAI
    int menorGlobal = vetor[0];
    for (int i = 1; i < N; i++)
    {
        if (vetor[i] < menorGlobal)
        {
            menorGlobal = vetor[i];
        }
    }

    // Espera os filhos terminarem e obter os retornos

    return 0;
}