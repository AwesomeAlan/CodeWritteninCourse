#include <cstdlib>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int partition_r(int arr[], int low, int high) {
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);
    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_r(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[100];
    clock_t start, finish;
    double duration;
    for (int i = 0; i < 100; ++i) {
        arr[i] = i + 1;
    }
    int n = sizeof(arr) / sizeof(arr[0]);
    start = clock();
    quickSort(arr, 0, n - 1);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;

    printf("Sorted array: \n");
    printArray(arr, n);
    printf("Running time: %f seconds\n", duration);
    printf("\n");
    return 0;
}