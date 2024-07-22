#include <iostream>
#include <pthread.h>
using namespace std;

void *tarefa1(void *x){
    cout << "Tarefa 1 Finalizada" << endl;
    return NULL;
}

void *tarefa2(void *x){
    cout << "Tarefa 2 Finalizada" << endl;
    return NULL;
}

int main(){

    // Declare 
    pthread_t th1, th2;

    // Create threads
    pthread_create(&th1, NULL, tarefa1, NULL);
    pthread_create(&th2, NULL, tarefa2, NULL);

    // Wait
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return (0);

}