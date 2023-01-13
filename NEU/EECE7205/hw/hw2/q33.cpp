#include <iostream>
using namespace std;

void countSort(int array[], int size) {
  int output[21];
  int count[21];
  int max = array[0];

  for (int i = 1; i < size; i++) {
    if (array[i] > max)
      max = array[i];
  }

  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    count[array[i]]++;
  }

  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    output[count[array[i]] - 1] = array[i];
    count[array[i]]--;
  }

  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

int main() {
    int array[] = {20, 18, 5, 7, 16, 10, 9, 3, 12, 14, 0};
    int n = sizeof(array) / sizeof(array[0]);
    clock_t start, finish;
    double duration;
    start = clock();
    countSort(array, n);
    finish = clock();
    cout << "Sorted array is: ";
    printArray(array, n);
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << duration << "seconds" "\n";
}