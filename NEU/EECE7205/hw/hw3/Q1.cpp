#include <iostream>
#include <algorithm>
#include <time.h>

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";
}

int partition_e(int a[], int p, int r) {
    int x = a[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        if(a[j] <= x){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[r]);
    return i+1;
}

int partition_w (int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i=l; i<r; i++)
		if (arr[i] == x)
		break;
	swap(&arr[i], &arr[r]);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}

int findMedian(int arr[], int n)
{
	std::sort(arr, arr+n); // Sort the array
	return arr[n/2]; // Return middle element
}

int Randomized_Partition(int a[], int p, int r) {
    int i = rand() % r + 1; //flag for debugging
    swap(&a[i], &a[r]);
    return partition_e(a, p, r);
}

int Randomized_Select_expected(int a[], int p, int r, int i) {
    if(p==r)
        return a[p];
    int q = Randomized_Partition(a,p,r);
    int k = q-p+1;
    if(i == k)
        return a[q];
    else if(i < k) {
        return Randomized_Select_expected(a, p, q-1, i);
    }
    else {
        return Randomized_Select_expected(a, q+1, r, i-k);
    }
}

int Randomized_Select_worst(int arr[], int l, int r, int k) {
	if (k > 0 && k <= r - l + 1) {
		int n = r-l+1; 
		int i, median[(n+4)/5]; 
		for (i=0; i<n/5; i++) median[i] = findMedian(arr+l+i*5, 5);
		if (i*5 < n) {
			median[i] = findMedian(arr+l+i*5, n%5);
			i++;
		}

		int medOfMed = (i == 1)? median[i-1]:
								Randomized_Select_worst(median, 0, i-1, i/2);

		int pos = partition_w(arr, l, r, medOfMed);

		if (pos-l == k-1)
			return arr[pos];
		if (pos-l > k-1) 
			return Randomized_Select_worst(arr, l, pos-1, k);

		return Randomized_Select_worst(arr, pos+1, r, k-pos+l-1);
	}
	return INT_MAX;
}

void shuffleRandom (int arr[], int n ) {
    srand ( time(NULL) );
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
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
    start = clock();
    std::cout << "K'th smallest element (with linear expected running time) is "
		<< Randomized_Select_expected(arr, 0, 99, 10) << std::endl;
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "Running time is: " << duration << "seconds" << std::endl << std::endl;

    start = clock();
    std::cout << "K'th smallest element (with linear worst-case running time) is "
		<< Randomized_Select_worst(arr, 0, 99, 10) << std::endl;
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "Running time is: " << duration << "seconds";
}
