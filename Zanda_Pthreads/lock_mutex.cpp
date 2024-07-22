#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_t Thread1, Thread2;     // Thread identifiers
pthread_mutex_t Mutex;          // Mutex variable

void *tarefa1(void *x){
    pthread_mutex_lock(&Mutex);
    cout << "Thread 1 on critical session" << endl;
    sleep(2);
    pthread_mutex_unlock(&Mutex);
    return NULL;
}

void *tarefa2(void *x){
    pthread_mutex_lock(&Mutex);
    cout << "Thread 2 on critical session" << endl;
    sleep(2);
    pthread_mutex_unlock(&Mutex);
    return NULL;
}

int main(){

    // Initialize mutex
    pthread_mutex_init(&Mutex, NULL);

    // Create threads
    pthread_create(&Thread1, NULL, tarefa1, NULL);
    pthread_create(&Thread2, NULL, tarefa2, NULL);

    // Wait for threads to finish
    pthread_join(Thread1, NULL);
    pthread_join(Thread2, NULL);

    cout << "Finished..." << endl;

    return 0;
}