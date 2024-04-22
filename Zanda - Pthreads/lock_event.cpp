#include <iostream>
#include <pthread.h>
using namespace std;

pthread_t Thread1, Thread2;
pthread_mutex_t mutex, eventMutex;
pthread_cond_t Event;
int numero = 0;

void *tarefa1( void *x ){
    for (int cont = 0; cont < 100; cont ++){
        pthread_mutex_lock(&mutex);
        numero ++;
        pthread_mutex_unlock(&mutex);
        cout << "Número = " << numero << endl;
        if ( numero == 50 ){
            pthread_cond_signal(&Event);
        }
    }
    cout << "Tarefa 1 terminou..." << endl;
    return NULL;
}

void *tarefa2( void  *x ){
    pthread_mutex_lock(&eventMutex);
    pthread_cond_wait(&Event, &eventMutex);
    pthread_mutex_unlock(&eventMutex);
    for ( int cont = 1; cont < 50; cont++ ){
        pthread_mutex_lock(&mutex);
        numero = numero + 20;
        pthread_mutex_unlock(&mutex);
        cout << "Número = " << numero << endl;
    }
    cout << "Tarefa 2 terminou..." << endl;
    return NULL;
}

int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&eventMutex, NULL);
    pthread_cond_init(&Event, NULL);

    pthread_create(&Thread1, NULL, tarefa1, NULL);
    pthread_create(&Thread2, NULL, tarefa2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&eventMutex);
    
    pthread_join(Thread1, NULL);
    pthread_join(Thread2, NULL);
}