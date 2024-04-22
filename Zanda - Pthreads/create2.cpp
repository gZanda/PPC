#include <iostream>
#include <pthread.h>
using namespace std;

void *hello(void *threadId) {
    long tid = (long)threadId;
    cout << "> Running Thread > " << tid << endl;
    pthread_exit(NULL);
}

int main(){

    // Declare
    pthread_t threads[5];
    long t; // thread identifier
    
    // Create threads using a loop and "t" as id
    for(t=0;  t<5; t++){
        cout << "Creating thread = " << t << endl;
        pthread_create(&threads[t], NULL, hello, (void *)t);
    }

    // Finish 
    pthread_exit(NULL);
}