#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <mutex>
#include <vector>
#include <thread>
#include <random>

#define NUM_THREADS 5

#define LEFT std::max(phnum,(phnum+1)%5)
#define RIGHT std::min(phnum,(phnum+1)%5)

std::mutex mu;
std::vector<std::mutex> forks(NUM_THREADS);
std::mt19937 Rng{std::random_device{}()};

int phi_eat[5];

void eat(int phnum) {
    auto eating_time{1};

#ifdef high_priority
    std::this_thread::sleep_for(std::chrono::seconds(phnum)); 
#endif

#ifdef even_forks
    if (phnum == 0) std::lock_guard<std::mutex> (forks[RIGHT], std::adopt_lock); 
    if (phnum == 1) std::lock_guard<std::mutex> (forks[LEFT], std::adopt_lock);
    if (phnum != 0 || phnum != 1) {
        std::lock_guard<std::mutex> (forks[LEFT], std::adopt_lock); 
        std::lock_guard<std::mutex> (forks[RIGHT], std::adopt_lock); 
    }
#else 
    std::lock_guard<std::mutex> (forks[LEFT], std::adopt_lock); 
    std::lock_guard<std::mutex> (forks[RIGHT], std::adopt_lock); 
#endif
#ifdef random_eating_time
    static thread_local std::uniform_int_distribution<> random_time(1, 10);
    eating_time = random_time(Rng);
#endif
    std::this_thread::sleep_for(std::chrono::seconds(eating_time));
    std::lock_guard<std::mutex> Lock(mu);
    std::cout << "Philosopher " << phnum << "\tfork:" << "\tleft " << LEFT << "\tright " << RIGHT << std::endl;
    phi_eat[phnum]++;
}

void philosopher(int phnum)
{
    while(phi_eat[phnum] < 2) {
        eat(phnum);
    }
}

int main() {
    int temp[NUM_THREADS] = {0, 1, 2, 3, 4};
    std::vector<std::thread> threadPool;
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threadPool.push_back(std::thread(philosopher, std::ref(temp[i])));
    }

    for (auto &th : threadPool)
    {
        th.join();
    }
    return 0;
}