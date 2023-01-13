#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#ifdef PARALLEL
#include <omp.h>
#endif

#include <cuda_runtime.h>

constexpr auto MaxNum{1000000};
constexpr auto NumClass{1 << 4};
constexpr auto Interval{MaxNum / NumClass};

template <typename T> auto populateRandomVector(std::vector<T> &Vec) {
  std::random_device RndDevice;
  std::mt19937 MersenneEngine{RndDevice()};
  std::uniform_int_distribution<T> Dist{0, MaxNum};
  std::generate(Vec.begin(), Vec.end(),
                [&Dist, &MersenneEngine]() { return (Dist(MersenneEngine)); });
}

template <typename T> auto histogramCpu(const std::vector<T> &Vec) {
#ifdef PARALLEL
#pragma omp parallel for
#endif
  std::vector<int> Hist(NumClass);
  for (auto I{0}; I < Vec.size(); ++I) {
    Hist[Vec[I] / Interval]++;
  }
  for (int i = 0; i < NumClass; i++) {
	   std::cout << Hist[i] << " ";
  }
  std::cout << std::endl;
  return Hist;
}

template <typename T>
__global__ void histogramGpu(const T *Vec, const std::size_t N,
                             const int Interval, int *Hist) {
  auto Tid{blockIdx.x * blockDim.x + threadIdx.x};
  if (Tid >= N)
    return;
  atomicAdd(&Hist[Vec[Tid] / Interval], 1);
}

int main(int argc, char **argv) {
  using T = int;

  //auto N{1 << 28};
  for (int i = 10; i <= 25; i += 5) {
  auto N = 1 << i;
  auto NumberSize{N * sizeof(T)};
  auto HistSize{NumClass * sizeof(int)};
  std::vector<T> HostVec(N);
  populateRandomVector(HostVec);

  T *DeviceVec = NULL;
  T *DeviceHist = NULL;

  float GpuElapsedTimeMs[4] = {0.0f, 0.0f, 0.0f, 0.0f};

  cudaEvent_t Start, Stop;
  cudaEventCreate(&Start);
  cudaEventCreate(&Stop);

  // Allocate memory
  cudaEventRecord(Start, 0);
  cudaMalloc(reinterpret_cast<void **>(&DeviceVec), NumberSize);
  cudaMalloc(reinterpret_cast<void **>(&DeviceHist), HistSize);
  cudaMemset(DeviceHist, 0, HistSize);
  cudaEventRecord(Stop, 0);
  cudaEventSynchronize(Stop);
  cudaEventElapsedTime(&GpuElapsedTimeMs[0], Start, Stop);

  // Copy data to device
  cudaEventRecord(Start, 0);
  cudaMemcpy(DeviceVec, HostVec.data(), NumberSize, cudaMemcpyHostToDevice);
  cudaEventRecord(Stop, 0);
  cudaEventSynchronize(Stop);
  cudaEventElapsedTime(&GpuElapsedTimeMs[1], Start, Stop);

  // Kernel configuration
  cudaEventRecord(Start, 0);
  dim3 ThreadsPerBlock (128);
  dim3 BlocksPerGrid = ((N + 127) / 128);

  histogramGpu<<<BlocksPerGrid, ThreadsPerBlock>>>(DeviceVec, N, Interval,
                                                   DeviceHist);
  cudaDeviceSynchronize();

  cudaEventRecord(Stop, 0);
  cudaEventSynchronize(Stop);
  cudaEventElapsedTime(&GpuElapsedTimeMs[2], Start, Stop);

  // copy it back
  cudaEventRecord(Start, 0);
  std::vector<T> FromDeviceHist(NumClass);
  cudaMemcpy(FromDeviceHist.data(), DeviceHist, HistSize,
                   cudaMemcpyDeviceToHost);

  cudaEventRecord(Stop, 0);
  cudaEventSynchronize(Stop);
  cudaEventElapsedTime(&GpuElapsedTimeMs[3], Start, Stop);

  // CPU
  auto CpuElapsedTimeMs{0.0f};
  cudaEventRecord(Start, 0);
  auto HostHist{histogramCpu(HostVec)};
  cudaEventRecord(Stop, 0);
  cudaEventSynchronize(Stop);
  cudaEventElapsedTime(&CpuElapsedTimeMs, Start, Stop);
  
  std::cout << "N = " << N << std::endl;
  std::cout << "Check passed? " << std::boolalpha
            << (FromDeviceHist == HostHist) << std::endl;
  std::cout << "GPU Time [ms]: ";
  std::for_each(std::begin(GpuElapsedTimeMs), std::end(GpuElapsedTimeMs),
                [&](float I) { std::cout << I << " "; });
  std::cout << std::endl;
  std::cout << "CPU Time [ms]: " << CpuElapsedTimeMs << std::endl;
  std::cout << "Speed up [xN]: "
            << CpuElapsedTimeMs /
                   (std::accumulate(std::begin(GpuElapsedTimeMs),
                                    std::end(GpuElapsedTimeMs), 0.0f))
            << " " << CpuElapsedTimeMs / GpuElapsedTimeMs[2] << std::endl;
  std::cout << "**********************************" << std::endl;
  cudaFree(DeviceVec);
  cudaFree(DeviceHist);
  }
  return EXIT_SUCCESS;
}

