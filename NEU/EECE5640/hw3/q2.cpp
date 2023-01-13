#include <semaphore>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

#define THREAD_NUM 8

using namespace std;

class Semaphore {
public:
  explicit Semaphore(int count = 0) : count_(count) {
  }

  void Signal() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++count_;
    cv_.notify_one();
  }

  void Wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [=] { return count_ > 0; });
    --count_;
  }

private:
  std::mutex mutex_;
  std::condition_variable cv_;
  int count_;
};

int arr[10001];
Semaphore g_semaphore(1);

bool check (int n) {
    if (n % 3 == 0 or n % 7 == 0) return true;
    return false;
}

void func (int start, int end) {
    g_semaphore.Wait();
    for(int i = start; i < end; i++) {
        if (i == 0) continue;
        if (check(i)) arr[i] = 1;
    }
    g_semaphore.Signal();
}

int main() {
    std::thread t[THREAD_NUM];
    int start, end;
    int chunk = 10000/THREAD_NUM;
    for (int i = 0; i < THREAD_NUM; i++) {
        start = i * chunk;
        end = start + chunk;
        t[i] = std::thread(func, start, end);
    }
    for (int i = 0; i < THREAD_NUM; i++) t[i].join();
    for (int i = 0; i < 10001; i++) {
        if (arr[i] == 1) cout << i << " ";
    }
    return 0;
}