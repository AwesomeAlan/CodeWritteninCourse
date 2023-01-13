//#include <bits/stdc++.h>
//using namespace std;
#include <time.h>
#include <iostream>
using namespace std;

void merge_array(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i=0;i<n1;i++) {
        L[i]=arr[l+i];
    }
    for (j=0;j<n2;j++) {
        R[j]=arr[m+1+j];
    }
    i=0; j=0; k=l; 
    while(i<n1&&j<n2) {
        if(L[i]<=R[j]) {
            arr[k]=L[i];
            i++;
        }
        else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2) {
        arr[k]=R[j];
        j++;
        k++;
    }
    return ;
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge_array(arr, l, m, r);
    }
    return ;
}

void insertionSort(int arr[], int length) {
      int i, j, tmp;
      for (i = 1; i < length; i++) {
            j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                  tmp = arr[j];
                  arr[j] = arr[j - 1];
                  arr[j - 1] = tmp;
                  j--;
            }
      }
}

int main() {
   int n = 100000;  
   int tmp = n;
   int arr[n];
   for(int i=0;i<tmp;i++){
       arr[i] = tmp;
       tmp--;
   }

    // int n = 1;
    // while(1) {
    //     int arr[n];
    //     int tmp = n;
    //     for(int i = 0; i<n; i++){
    //         arr[i] = tmp;
    //         tmp--;
    //     }
    //     clock_t insertion_time_start = clock();
    //     insertionSort(arr, n);
    //     clock_t insertion_time_end = clock();
    //     cout << "Processing time of insertion sort : " << (float)(insertion_time_end - insertion_time_start)/CLOCKS_PER_SEC << " seconds" << endl;

    //     clock_t merge_time_start = clock();
    //     merge_sort(arr, 0, n-1); 
    //     clock_t merge_time_end = clock();
    //     cout << "Processing time of merge sort : " << (float)(merge_time_end - merge_time_start)/CLOCKS_PER_SEC << " seconds" << endl;

    //     if((merge_time_end - merge_time_start)<(insertion_time_end - insertion_time_start)){
    //         cout << n << endl;
    //         return 0;
    //     }
    //     n++;
    // }
    
    clock_t insertion_time_start = clock();
    insertionSort(arr, n);
    clock_t insertion_time_end = clock();

    tmp = n;
    for(int i=0;i<tmp;i++){
        arr[i] = tmp;
        tmp--;
    }

    clock_t merge_time_start = clock();
    merge_sort(arr, 0, n-1); 
    clock_t merge_time_end = clock();
    cout << "Input size(n) : " << n << endl;
    cout << "Processing time of insertion sort : " << (float)(insertion_time_end - insertion_time_start)/CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Processing time of merge sort : " << (float)(merge_time_end - merge_time_start)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}