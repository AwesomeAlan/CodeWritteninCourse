#include <iostream>
#include <iomanip>
using namespace std;

float taylor_f(int n, float x) {
	float sum = 1.0f;

	for (int i = n - 1; i > 0; --i)
		sum = 1 + x * sum / i;

	return sum;
}

double taylor_d(int n, double x) {
	double sum = 1.0;

	for (int i = n - 1; i > 0; --i)
		sum = 1 + x * sum / i;

	return sum;
}

float calculate_f(int n, float x) {
    float sum = 1 / x + taylor_f(n, x);
    return sum;
}

double calculate_d(int n, double x) {
    double sum = 1 / x + taylor_d(n, x);
    return sum;
}

int main() {
	int n = 10;
	float x1 = 1, x2 = 10, x3 = 100, x4 = 1000;
    double y1 = 1, y2 = 10, y3 = 100, y4 = 1000;
    cout << "Single precision:" << endl;
	cout << "e^x(x=1) = " << setprecision(16) << calculate_f(n, x1) << endl;
    cout << "e^x(x=10) = " << setprecision(16) << calculate_f(n, x2) << endl;
    cout << "e^x(x=100) = " << setprecision(16) << calculate_f(n, x3) << endl;
    cout << "e^x(x=1000) = " << setprecision(16) << calculate_f(n, x4) << endl << endl;
    cout << "Double precision:" << endl;
    cout << "e^x(x=1) = " << setprecision(16) << calculate_d(n, y1) << endl;
    cout << "e^x(x=10) = " << setprecision(16) << calculate_d(n, y2) << endl;
    cout << "e^x(x=100) = " << setprecision(16) << calculate_d(n, y3) << endl;
    cout << "e^x(x=1000) = " << setprecision(16) << calculate_d(n, y4) << endl;
	return 0;
}

