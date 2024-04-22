#include <iostream>
#include <pthread.h>
using namespace std;

pthread_t Thread1, Thread2, Thread3, Thread4;
pthread_rwlock_t rwlock;

void *escritor1(void *x){
    pthread_rwlock_wrlock(&rwlock);
    cout << "Thread Escritor" << endl;
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *leitor1(void *x){
    pthread_rwlock_rdlock(&rwlock);
    cout << "Thread Leitor" << endl;
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *escritor2(void *x){
    pthread_rwlock_wrlock(&rwlock);
    cout << "Thread Escritor" << endl;
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *leitor2(void *x){
    pthread_rwlock_rdlock(&rwlock);
    cout << "Thread Leitor" << endl;
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main(){

    // Initialize rwlock
    pthread_rwlock_init(&rwlock, NULL);

    // Create threads
    pthread_create(&Thread1, NULL, escritor1, NULL);
    pthread_create(&Thread2, NULL, leitor1, NULL);
    pthread_create(&Thread3, NULL, escritor2, NULL);
    pthread_create(&Thread4, NULL, leitor2, NULL);

    // Wait for threads to finish
    pthread_join(Thread1, NULL);
    pthread_join(Thread2, NULL);
    pthread_join(Thread3, NULL);
    pthread_join(Thread4, NULL);

    cout << "Finished..." << endl;

    return 0;
}