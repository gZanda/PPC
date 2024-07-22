#include <iostream>
#include <pthread.h>
using namespace std;

pthread_t Thread1, Thread2;
pthread_mutex_t mutex;
int totalSum = 0;
int evenNumbers = 0;
int oddNumbers = 0;

void *evens(void *inputNumber) {
    cout << "Thread computing Evens" << endl;

    int input = *(int*)inputNumber;
    for (int i = 2; i <= input; i += 2) {
        pthread_mutex_lock(&mutex);
        totalSum += i;
        evenNumbers++;
        pthread_mutex_unlock(&mutex);
        cout << "Even Number: " << i << endl;
    }

    return NULL;
}

void *odds(void *inputNumber) {
    cout << "Thread computing Odds" << endl;

    int input = *(int*)inputNumber;
    for (int i = 1; i <= input; i += 2) {
        pthread_mutex_lock(&mutex);
        totalSum += i;
        oddNumbers++;
        pthread_mutex_unlock(&mutex);
        cout << "Odd Number: " << i << endl;
    }

    return NULL;
}

int main(){

    int n;

    cout << "Enter an Integer Number" << endl;

    cin >> n;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&Thread1, NULL, evens, (void *)&n);
    pthread_create(&Thread2, NULL, odds, (void *)&n);

    pthread_join(Thread1, NULL);
    pthread_join(Thread2, NULL);

    cout << endl << endl <<"Total Sum: " << totalSum << endl;
    cout << "Even Numbers: " << evenNumbers << endl;
    cout << "Odd Numbers: " << oddNumbers << endl;

    return 0;
}