#include <algorithm>
#include <curand.h>
#include <curand_kernel.h>
#include <iostream>
#include <iomanip>
#include <numeric>

#ifdef PARALLEL
#include <omp.h>
#endif

#include <cuda_runtime.h>

constexpr auto NThread{1024};
constexpr auto NIter{1000000};

__global__ void setupRandomState(curandState *State) {
  auto Tid{threadIdx.x + blockDim.x * blockIdx.x};
  if (Tid > NThread)
    return;
  curand_init(1234, Tid, 0, &State[Tid]);
}

__device__ void calculatePi(curandState *State, unsigned int Tid, int &Count) {
  auto DevCount{0};
  for (auto I{0}; I < NIter; ++I) {
    auto X{curand_uniform(&State[Tid])};
    auto Y{curand_uniform(&State[Tid])};
    DevCount += (std::pow(X, 2) + std::pow(Y, 2) <= 1);
  }
  Count = DevCount;
}

__global__ void calculatePiGpu(int *Sum, curandState *State) {
  auto Tid{blockIdx.x * blockDim.x + threadIdx.x};
  if (Tid > NThread)
    return;
  auto DevCount {0};
  calculatePi(State, Tid, DevCount);
  atomicAdd(&Sum[Tid], DevCount);
}

int main(int argc, char **argv) {
  using T = double;
  auto TotSize{sizeof(int) * NThread};

  int ThreadsPerBlock = 128;
  int BlocksPerGrid = (NThread + ThreadsPerBlock - 1) / ThreadsPerBlock;

  // Set random state
  curandState *State;
  cudaMalloc(&State, sizeof(curandState) * NThread);
  setupRandomState<<<BlocksPerGrid, ThreadsPerBlock>>>(State);

  int *HostSum = nullptr;
  int *DeviceSum = nullptr;
  HostSum = (int *)malloc(TotSize);
  memset(HostSum, 0, TotSize);
  cudaMalloc(reinterpret_cast<void **>(&DeviceSum), TotSize);
  cudaMemset(DeviceSum, 0, TotSize);

  calculatePiGpu<<<BlocksPerGrid, ThreadsPerBlock>>>(DeviceSum, State);
  cudaMemcpy(HostSum, DeviceSum, TotSize, cudaMemcpyDeviceToHost);

    // std::for_each(HostSum, HostSum + NThread,
    //               [&](T I) { std::cout << I << " "; });
  std::cout << std::setprecision(32) << static_cast<T> (std::accumulate(HostSum, HostSum+NThread, 0) * 4.0 / NThread / NIter) << std::endl;

  return EXIT_SUCCESS;
}

