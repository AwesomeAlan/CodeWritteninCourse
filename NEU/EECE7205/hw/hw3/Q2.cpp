#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int max(int a, int b) {
	return (a > b)? a : b;
}

int lcs(char *str1, char *str2, int l1, int l2) {
	if (l1 == 0 || l2 == 0)
		return 0;
	if (str1[l1-1] == str2[l2-1])
		return 1 + lcs(str1, str2, l1-1, l2-1);
	else
		return max(lcs(str1, str2, l1, l2-1), lcs(str1, str2, l1-1, l2));
}

int main() {
    clock_t start, finish;
    double duration;
	char str1[] = "ADFHAGHTSDFGFDSGFADFADF";
	char str2[] = "SAGHGFSSDFADATDGSDFGADF";
	int l1 = strlen(str1);
	int l2 = strlen(str2);
	start = clock();
	cout<<"Length of LCS is " << lcs(str1, str2, l1, l2) << endl;
    finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "Running time is: " << duration << " seconds";
	return 0;
}
