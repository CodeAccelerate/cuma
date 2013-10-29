#ifndef __SCOPEPROFILE_H
#define __SCOPEPROFILE_H

#include <vector>
#include <map>
#include <sys/time.h>
#include <string>

namespace utility {
struct StepProfile{
  std::string Desc;
  struct timeval StepStart;
  struct timeval StepEnd;
  long Interval;
};

void showProfileResult(const std::vector<StepProfile> & profilers);
void showProfileResult(const std::map<std::string, long> & profilers);

class ScopeProfile{
public:
  ScopeProfile(const std::string &desc);
  ~ScopeProfile();

protected:
  void calcDiffTime();
  //  std::vector<StepProfile> *mEntries;
  std::string mDescription;
  struct timeval mStart;
  struct timeval mEnd;
  long mInterval;

};

class CPUScopeProfile : public ScopeProfile{
public:
  CPUScopeProfile(const std::string &desc);
  ~CPUScopeProfile();

private:
  //  std::vector<StepProfile> *mEntries;
};

class GPUScopeProfile : public ScopeProfile{
public:
  GPUScopeProfile(const std::string &desc);
  ~GPUScopeProfile();

private:
  //  std::vector<StepProfile> *mEntries;

};

}

#endif
