#include <iostream>
#include <vector>
#include "mpi.h"
#include <cstdlib>

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

    MPI_Bcast(array, num, MPI_INT, 0, MPI_COMM_WORLD);

    int out = 0;
    for (int i = 0; i < num; i++) {
        if (array[i] / interval == myid) out++;
    }

    MPI_Gather(&out, 1, MPI_INT, recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (myid == 0) {
        for (int i: recv) cout << i << " ";
        cout << endl;
    }
    time(&end);
    if (myid == 0) {
        double time_taken = double(end - start);
        cout << time_taken << endl;
    }
    MPI_Finalize();

    return 0;
}