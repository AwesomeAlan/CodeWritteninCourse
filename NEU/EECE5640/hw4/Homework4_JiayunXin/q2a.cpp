#include <iostream>
#include <vector>
#include "mpi.h"
#include <cstdlib>
#include <string>

using namespace std;
const int range = 1000;
const int num = 1024 * 1024;

int main(int argc,char **argv) {
    time_t start, end;
    int myid, comm_sz;
    int array[num];

    time(&start);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
    
    int recv[comm_sz] = {};
    int interval = range / comm_sz;
    int count[comm_sz] = {};
    
    srand((unsigned)time(NULL));

    if (myid == 0) {
        for (int i = 0; i < num; i++) {
            array[i] = rand() % range + 1;
        }
    }

    int nportion = num/comm_sz;
    int rarray[nportion];
    MPI_Scatter(array, nportion, MPI_INT, rarray, nportion, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < nportion; i++) {
        count[rarray[i]/interval]++;
    }

    MPI_Reduce(count, recv, comm_sz, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    time(&end);
    if (myid == 0) {
        //for (int i: recv) cout << std::string(i/1024/16, '*') << "\n";
        double time_taken = double(end - start);
        for (int i: recv) cout << i << " ";
        cout << endl;
        cout << time_taken << endl;
    }
    MPI_Finalize();
    return 0;
}