#include <cstdlib>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "omp.h"

using namespace std;

int main(int argc, char *argv[])
{
    size_t M = 512;
    size_t N = 512;
    int matrix[M][M];
    int vector[M];
    int out[M];
    std::fill(*matrix, *matrix + M*N, M*N);
    for (int i = 0; i<512; i++) vector[i] = i;

    for (int i=0; i<512; i++){
         out[i] = 0;
    }

    for (int i=0; i<512; i++){
        #pragma omp for
        for (int j=0; j<512; j++){
            out[i]+=(matrix[i][j]*vector[j]);
        }
    }

    for (int i=0; i<512; i++){
        cout<< out[i]<<"  "<<endl;
    }

    system("PAUSE");
    return EXIT_SUCCESS;
}