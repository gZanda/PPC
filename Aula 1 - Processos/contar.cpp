#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int somaPares() {
    int soma = 0;
    for (int i = 2; i <= 100; i += 2) {
        soma += i;
    }
    return soma;
}

int somaImpares() {
    int soma = 0;
    for (int i = 1; i <= 100; i += 2) {
        soma += i;
    }
    return soma;
}

int main() {
    pid_t pid = fork();

    // Filho ( quando pid é igual a 0 )
    if (pid == 0) {
        int soma_impares = somaImpares();
        cout << "Processo filho: Soma dos valores ímpares de 1 a 100: " << soma_impares << endl;
    } 
    // Pai ( qundo pid é maior que 0 )
    else if (pid > 0) {
        int soma_pares = somaPares();
        cout << "Processo pai: Soma dos valores pares de 1 a 100: " << soma_pares << endl;

        // Aguarda QUALQUER processo filho terminar
        wait(NULL);
    } 
    // Erro ( Quando pid é menor que 0 )
    else {
        cerr << "Erro ao criar o processo filho." << endl;
        return 1;
    }

    return 0;
}
