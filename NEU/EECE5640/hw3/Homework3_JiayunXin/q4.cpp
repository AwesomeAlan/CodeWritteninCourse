#include <cstdlib>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;


int main(int argc, char *argv[])
{
    //initialize matrix
    size_t M = 512;
    size_t N = 512;
    int matrix[M][M];
    int vector[M];
    int out[M];

    std::fill(*matrix, *matrix + M*N, 1);
    for (int i = 0; i<512; i++) vector[i] = i;
    for (int i=0; i<512; i++){
         out[i] = 0;
    }

    omp_set_num_threads(8);

    #pragma omp parallel for reduction(+:out)
    for (int i=0; i<512; i++){
        cout << ' ' << omp_get_thread_num() << ' ' ;
        for (int j=0; j<512; j++){
            #pragma omp critical
            out[i]+=(matrix[i][j]*vector[j]);
        }
    }

    // #pragma omp parallel 
    // #pragma omp critical
    // int threadid = omp_get_thread_num();
    // int total = omp_get_num_threads();
    // cout << "Process " << omp_get_thread_num() << " out of " << omp_get_num_threads() << endl;

    for (int i=0; i<512; i++){
        cout<< out[i]<<"  ";
    }
    cout << endl;
    return 0;
}
