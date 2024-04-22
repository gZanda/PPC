#include <iostream>
#include <cstdlib>
#include <ctime>
#include "pthread.h"
using namespace std;

// Lock Mutex
pthread_mutex_t mutex;

// Memória Compartilhada
const int SIZE = 500000;
int vet[SIZE];
int n, x;
int ocorrencias = 0;
int part_size = 0;
int part_extra = 0;

// Tarefa a ser executada pelas threads
// a = número da partição
void *tarefa1(void *param_a){

    long a = (long)param_a;
    int pos_inicial = a*part_size; // Posição inicial da partição
    int pos_final = ((a+1)*part_size)-1; // Poisição limite da partiçã

    // Se for a última partição ( precisa ir um pouco mais )
    if( a == n-1){
        for(int i = pos_inicial; i <= pos_final+part_extra; i++){
            if( vet[i] == x){
                pthread_mutex_lock(&mutex);
                ocorrencias++;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    // Se não for a última partição, ela tem o tamanho normal ( igual o das outras )
    else{
        for(int i = pos_inicial; i <= pos_final; i++){
            if( vet[i] == x){
                pthread_mutex_lock(&mutex);
                ocorrencias++;
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    return nullptr;
}

// Função para descobrir o tamanho bruto das porções do array - ( Inteiro )
int bruto(int entrada_n){

    int n = entrada_n;
    int bruto = SIZE/n;

    return bruto;
}

// Função para descobrir o tamanho adicional de uma porção do araay - ( caso 500.000/n não seja exato )
int adicional(int v_bruto){

    int bruto = v_bruto;
    int adicional = SIZE - (bruto*n);

    return adicional;
}

int main(){

    // Lock Mutex Init
    pthread_mutex_init(&mutex, NULL);

    // Preencher o vetor com números aleatórios - ( 500.000 posições )
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++){
        int x = rand();
        vet[i] = x;
        cout << vet[i] << " ";
    }
    cout << endl << endl << " ------------------ " << endl << endl;
    cout << "Array Preenchido..." << endl;

    // Entradas do usuário
    cout << "> Número de Threads: ";
    cin >> n;
    cout << "> Número Inteiro: ";
    cin >> x;

    // Descobrir tamanho das partições do array - ( que será particionado em "n" partições )

    part_size = bruto(n);
    part_extra = adicional(part_size);

    // Criar "n" threads
    pthread_t threads[n];
    for( long i = 0; i < n; i++ ){
        pthread_create(&threads[i],NULL,tarefa1,(void *)i);
    }

    // Join ( esperar as "n" threads terminarem )
    for( int i = 0; i < n; i++ ){
        pthread_join (threads[i], NULL);
    }

    // Output do resultado
    cout << endl << " ------------------ " << endl << endl;
    if(ocorrencias == 0){
        cout << "Número Não Encontrado" << endl;
    }
    else{
        cout << "Número encontrado " << ocorrencias << " vez(es)" << endl;
    }
    cout << endl;

    // Destrói Mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}