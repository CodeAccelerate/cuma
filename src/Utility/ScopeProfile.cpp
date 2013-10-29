#include "ScopeProfile.h"
#include <iostream>
#include <cuda_runtime_api.h>
using namespace std;



namespace utility {

std::vector<StepProfile> gProfile;
std::map<std::string, long> gProfileGroup;

ScopeProfile::ScopeProfile(const string &desc):
  mDescription(desc)
{
   cudaThreadSynchronize();
    gettimeofday(&mStart, NULL); 
}


ScopeProfile::~ScopeProfile()
{
  gettimeofday(&mEnd, NULL); 
  calcDiffTime();
  StepProfile entry;
  entry.Desc = mDescription;
  entry.StepStart = mStart;
  entry.StepEnd = mEnd;
  entry.Interval = mInterval;
  //  if (mInterval > 10000)
  //    printf("%s slowing...takes %d ms\n",  mDescription.c_str(), mInterval/1000);
  gProfile.push_back(entry);
  gProfileGroup[mDescription] += mInterval;
}


void ScopeProfile::calcDiffTime()
{
  mInterval = (mEnd.tv_sec-mStart.tv_sec)*1000000.0 + mEnd.tv_usec-mStart.tv_usec;
}


// CPU version
CPUScopeProfile::CPUScopeProfile(const string &desc):
  ScopeProfile(desc)
{
    gettimeofday(&mStart, NULL); 
}


CPUScopeProfile::~CPUScopeProfile()
{
}


// GPU version
GPUScopeProfile::GPUScopeProfile(const string &desc):
  ScopeProfile(desc)
{
  cudaThreadSynchronize();
    gettimeofday(&mStart, NULL); 
}


GPUScopeProfile::~GPUScopeProfile()
{
  cudaThreadSynchronize();
}





void showProfileResult(const std::vector<StepProfile> & profilers)
{
  for (std::vector<StepProfile>::const_iterator p= profilers.begin(); p != profilers.end(); p++)
    {
      //        printf("Iteration(%d) time %ld us = %ld ms.\n", iter, (*p).Interval, (*p).Interval/1000);
      std::cout << (*p).Desc << " took " << (*p).Interval << " us " << (*p).Interval/1000.0 << " ms." << std::endl;
    }
}

void showProfileResult(const std::map<std::string, long> & profilers)
{
  for (std::map<std::string, long>::const_iterator p= profilers.begin(); p != profilers.end(); p++)
    {
      //        printf("Iteration(%d) time %ld us = %ld ms.\n", iter, (*p).Interval, (*p).Interval/1000);
      std::cout << (*p).first << " took " << (*p).second << " us " << (*p).second/1000.0 << " ms." << std::endl;
    }
}

}
