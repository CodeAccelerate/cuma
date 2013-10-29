#include "NeUtility.h"
#include <iostream>
#include <cassert>
#include <cstdio>
/* return true if lhs is no worse than rhs */
bool compareProp(const cudaDeviceProp &lhs, const cudaDeviceProp &rhs)
{
  if (lhs.major > rhs.major)
    return true;
  else if (lhs.major < rhs.major)
    return false;
  
  if (lhs.minor > rhs.minor)
    return true;
  else if (lhs.minor < rhs.minor)
    return false;
  
  if (lhs.clockRate> rhs.clockRate)
    return true;
  else if (lhs.clockRate < rhs.clockRate)
    return false;
  return true;
}

void NeUseDevice(cudaDeviceProp *devProp, int devId)
{
  if (devId < 0) // choose the best 
    {
      int devCount;
      cudaGetDeviceCount(&devCount);
      int bestId = 0;
      for (int d = 0; d != devCount; d++)
        {
          cudaDeviceProp idevProp;
          cudaGetDeviceProperties(&idevProp, d);
          if (d == 0)
            *devProp = idevProp;
          else
            if (!compareProp(*devProp, idevProp))
              {
                *devProp = idevProp;
                bestId = d;
              }
        }
      std::cout << "choosing device id " << bestId << ".\n";
      cudaError_t error = cudaChooseDevice(&bestId, devProp);
      assert(error == cudaSuccess);
    }
  else 
    {
      std::cout << "choosing device id " <<devId << ".\n";
      cudaError_t error = cudaChooseDevice(&devId, devProp);
      assert(error == cudaSuccess);
    }
  std::cout << "choosing device " << devProp->name  << " num multiprocessors: "<<  devProp->multiProcessorCount 
            << " maxThreadsPerBlock: " << devProp->maxThreadsPerBlock
            << " global memory: " << (double)devProp->totalGlobalMem/(1<<30) << "GB"
            << std::endl;
}


void CHECK_KERNEL_ERROR(const char *info)                                                          
{                                                                                                  
#ifdef _DEBUG                                                                                      
  cudaThreadSynchronize();                                                                         
    cudaError_t error = cudaGetLastError();                                                        
                                                                                                   
      if (error != cudaSuccess)                                                                    
        printf("error in %s. error info %s error code %d\n", info, cudaGetErrorString(error), error);   
        assert(error == cudaSuccess);                                                                   
          //  CUT_CHECK_ERROR(info);                                                                    
#endif                                                                                              
}

