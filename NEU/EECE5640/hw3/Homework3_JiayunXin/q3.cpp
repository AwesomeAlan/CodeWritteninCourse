#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <mutex>
#include <vector>
#include <thread>
#include <omp.h>

using namespace std;

#define NUM_THREADS 5
#define NUM_CHOPS 5
omp_lock_t writelock[NUM_CHOPS];

int phi_eat[5];

bool test() {
    for (int i = 0; i < NUM_THREADS; i++) {
        if (phi_eat[i] == 0) {
            return false;
        }
    }
    cout << "Dinner is done!";
    return true;
}

void eat(int i)
{
    sleep(1);
    //int i = omp_get_thread_num();
    int left = max(i,(i+1)%5);
    int right = min(i,(i+1)%5);
    phi_eat[i] = 1;
    
    omp_set_lock(&writelock[left]);
    omp_set_lock(&writelock[right]);
        sleep(1);
        cout << "Philosopher " << omp_get_thread_num() << endl;
        cout << "Philosopher " << i << "\tleft " << left << "\tright " << right << endl;
    omp_unset_lock(&writelock[right]);
    omp_unset_lock(&writelock[left]);
}

void philosopher(int i) {
    // sleep(1);
    while (phi_eat[i] < 1)
    {
        eat(i);
    }
}

int main() {
    omp_set_num_threads(NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++) {
		omp_init_lock(&writelock[i]);
	}

    int i;
    #pragma omp parallel for private(i)
    for (i = 0; i < NUM_THREADS; i++) {
        philosopher(i);
    }

    return 0;        
}
