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
omp_lock_t writelock[NUM_THREADS];

//#define LEFT max(phnum,(phnum+1)%5)
//#define RIGHT min(phnum,(phnum+1)%5)

// std::mutex cout_mutex;
// std::vector<std::mutex> forks(NUM_THREADS);

// pthread_mutex_t mu[NUM_THREADS];
// pthread_mutex_t cout_lock;
int phi_eat[5];

bool test() {
    for (int i = 0; i < NUM_THREADS; i++) {
        if (phi_eat[i] == 0) {
            return false;
        }
    }
    return true;
    cout << "Dinner is done!";
}

// void take_fork(int phnum) {
//     pthread_mutex_lock(&mu[LEFT]);
//     pthread_mutex_lock(&mu[RIGHT]);
//     // int rc = pthread_mutex_lock(&cout_lock);
//     std::lock_guard<std::mutex> Lock(cout_mutex);
//     cout << ' ' << phnum << ' ' << LEFT << ' ' << RIGHT << " take" << endl;
//     pthread_mutex_unlock(&cout_lock);
//     sleep(1);
// }

// void put_fork(int phnum) {
//     pthread_mutex_unlock(&mu[LEFT]);
//     pthread_mutex_unlock(&mu[RIGHT]);
//     // int rc = pthread_mutex_lock(&cout_lock);
//     std::lock_guard<std::mutex> Lock(cout_mutex);
//     cout  << phnum << ' ' << LEFT << ' ' << RIGHT << " put" << endl;
//     // pthread_mutex_unlock(&cout_lock);
//     phi_eat[phnum] = 1;
//     sleep(1);
// }

// void *philosopher(void *arg) { 
//     int i = *((int *)arg);
//     sleep(1);
//     // cout << i << endl;
//     while (!test()) {
//         take_fork(i);
//         put_fork(i);
//     }
//     return 0;
// }

void eat(int i)
{
    // std::lock_guard<std::mutex> (forks[LEFT], std::adopt_lock); 
    // std::lock_guard<std::mutex> (forks[RIGHT], std::adopt_lock); 
    omp_set_lock(&writelock[i]);
        sleep(1);
        cout << "Philosopher" << i << endl;
    omp_unset_lock(&writelock[i]);
    // std::lock_guard<std::mutex> Lock(cout_mutex);
    // cout << "Philosopher " << phnum << "\tleft " << LEFT << "\tright " << RIGHT << endl;
    // print(LEFT, RIGHT, phnum);
    
    phi_eat[i] = 1;
}

void philosopher(int i) {
    // sleep(1);
    while (!test())
    {
        eat(i);
    }
}

int main() {
    omp_set_num_threads(NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++) {
		omp_init_lock(&writelock[i]);
	}

    #pragma omp parallel for private(i)
    for (int i = 0; i < NUM_THREADS; i++) {
        philosophize(i);
    }

    getchar();

    //int temp[NUM_THREADS] = {0, 1, 2, 3, 4};
    //std::vector<std::thread> threadPool;
    // for (int i = 0; i < NUM_THREADS; ++i)
    // {
    //     std::cout << i << std::endl;
    //     // threadPool.push_back(std::thread(new_philosopher, std::ref(temp[i])));
    //     threadPool.push_back(std::thread(new_philosopher, std::ref(temp[i])));
    // }

    // for (auto &i : threadPool)
    // {
    //     i.join();
    // }
    return 0;        
}