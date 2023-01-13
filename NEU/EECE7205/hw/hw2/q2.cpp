#include <iostream>
#include <time.h>

using namespace std;

void heapify (int arr[], int n, int i) {
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
 
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort (int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
 
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << "\n";
}

void changeValues (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleRandom ( int arr[], int n ) {
    srand ( time(NULL) );
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        changeValues(&arr[i], &arr[j]);
    }
}

int main() {
    int arr_size = 100;
    int arr[arr_size];
    clock_t start, finish;
    double duration;
    for (int i = 0; i < arr_size; i++) {
        arr[i] = i + 1;
    }
    shuffleRandom (arr, arr_size);
    cout << "Random permutation array is: \n";
    printArray(arr, arr_size);
    cout << "\n";

    start = clock();
    heapSort(arr, arr_size);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "Sorted array is: \n";
    printArray(arr, arr_size);
    cout << "\n";
    printf("Running time: %f seconds\n", duration);
}