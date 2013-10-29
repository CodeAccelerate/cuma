#pragma once 

#include <cuda_runtime.h>
#include <assert.h>
#define MAX_PRINT_SIZE 32


void NeUseDevice(cudaDeviceProp *devProp, int devId = -1);
void CHECK_KERNEL_ERROR(const char *info);

