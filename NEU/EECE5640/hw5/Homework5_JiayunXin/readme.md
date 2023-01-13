Homework5
Jiayun Xin

Apply for GPU: 
srun --partition=gpu --nodes=1 --pty --export=All --gres=gpu:1 --mem=1G --time=00:30:00 /bin/bash

Q1
preprocess: 
module load openmpi
module load cuda/11.3

a.
Compile: nvcc q1.cu -arch=sm_37
Execute: ./a.out

b.
Compile: nvcc q1.cu -arch=sm_37 -DPARALLEL
Execute: ./a.out

Q2a
Compile: nvcc q2.cu -o q2
Execute: ./q2

Compile: nvcc q2t.cu -o q2t
Execute: ./q2t

Q4
Compile: nvcc q4.cu
Execute: ./q4