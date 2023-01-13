#include<iostream>
#include<algorithm>
using namespace std;
void display(int *array, int size) {
   for(int i = 0; i<size; i++)
      cout << array[i] << " ";
   cout << endl;
}
int getMax(int array[], int size) {
   int max = array[1];
   for(int i = 2; i<=size; i++) {
      if(array[i] > max)
         max = array[i];
   }
   return max; 
}
void countSort(int *array, int size) {
    int output[size+1];
//    int max = getMax(array, size);
    int count[size+1]; 
//    for(int i = 0; i<=max; i++)
//       count[i] = 0;    
//    for(int i = 1; i <=size; i++)
//       count[array[i]]++;
//    for(int i = 1; i<=max; i++)
//       count[i] += count[i-1];  
//    for(int i = size; i>=1; i--) {
//       output[count[array[i]]] = array[i];
//       count[array[i]] -= 1;
//    }
//    for(int i = 1; i<=size; i++) {
//       array[i] = output[i];
//    }
//     int count[RANGE + 1], i;
//     memset(count, 0, sizeof(count));
 
    // Store count of each character
    for (int i = 0; array[i]; ++i)
        ++count[array[i]];
 
    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (int i = 1; i <= size; ++i)
        count[i] += count[i - 1];
 
    // Build the output character array
    for (int i = 0; array[i]; ++i) {
        output[count[array[i]] - 1] = array[i];
        --count[array[i]];
    }
 
    /*
    For Stable algorithm
    for (i = sizeof(arr)-1; i>=0; --i)
    {
        output[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }
     
    For Logic : See implementation
    */
 
    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (int i = 0; array[i]; ++i)
        array[i] = output[i];
}
int main() {
    int n = 11;
    int arr[11] = {20, 18, 5, 7, 16, 10, 9, 3, 12, 14, 0};
    cout << "Array before Sorting: ";
    display(arr, n);
    countSort(arr, n);
    cout << "Array after Sorting: ";
    display(arr, n);
}