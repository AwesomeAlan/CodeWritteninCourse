#include <iostream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

using namespace std;


int main(int argc, char* argv[]) {
    long niter = 10000;
    double x,y;                     
    int count = 0;                   
    double pi;
    int myid;
    int total;
    int nodenum;
    time_t start, end;
    time(&start);
    MPI_Init(&argc, &argv);                
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); 
    MPI_Comm_size(MPI_COMM_WORLD, &nodenum);

    for (int i = 0; i < niter; i++) {
        x = ((double)rand())/RAND_MAX;
        y = ((double)rand())/RAND_MAX;
        if (x*x + y*y < 1) count++;
    }
    //cout << 4.0*count/niter << endl;
    MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    time(&end);
    if (myid == 0) {
        cout << 4.0 * total / niter / nodenum << endl;
        double time_taken = double(end - start);
        cout << fixed;
        cout << time_taken << endl;
        cout << 1-(abs(4.0 * total / niter / nodenum - M_PI)/M_PI) << endl;
    }
    MPI_Finalize(); 
    return 0;
}