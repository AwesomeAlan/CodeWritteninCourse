#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

template <typename T>
T calculate(int n, T x) {
	T sum = 1.0;

	for (int i = n - 1; i > 0; --i)
		sum = 1 + x * sum / i;

	return 1/x+sum;
}


int main() {
    clock_t start, end;	
    int n = 100;
    float x1 = 1, x2 = 10, x3 = 100, x4 = 1000;
    double y1 = 1, y2 = 10, y3 = 100, y4 = 1000;
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        calculate(n, x1);
    }
    // cout << "Single precision:" << endl;
    // cout << "e^x(x=1) = " << setprecision(16) << calculate_f(n, x1) << endl;
    // cout << "e^x(x=10) = " << setprecision(16) << calculate_f(n, x2) << endl;
    // cout << "e^x(x=100) = " << setprecision(16) << calculate_f(n, x3) << endl;
    // cout << "e^x(x=1000) = " << setprecision(16) << calculate_f(n, x4) << endl << endl;
    end = clock();
    cout << "Running time: " << (double)(end-start)/CLOCKS_PER_SEC << "second" << endl;
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        calculate(n, y1);
    }
    // cout << "Double precision:" << endl;
    // cout << "e^x(x=1) = " << setprecision(16) << calculate_f(n, y1) << endl;
    // cout << "e^x(x=10) = " << setprecision(16) << calculate_f(n, y2) << endl;
    // cout << "e^x(x=100) = " << setprecision(16) << calculate_f(n, y3) << endl;
    // cout << "e^x(x=1000) = " << setprecision(16) << calculate_f(n, y4) << endl;
    end = clock();
    cout << "Running time: " << (double)(end - start)/CLOCKS_PER_SEC << "second" << endl;
    return 0;
}
