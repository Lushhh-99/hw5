#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

     size_t numWorker=avail[0].size();
     size_t numDay=avail.size();
     vector<int> worked(numWorker, 0);
    //initializes a schedule
     sched=DailySchedule(numDay, vector<Worker_T>());
     return canWork(avail, dailyNeed, maxShifts, sched, 0, 0, worked);




}
bool canWork(const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, size_t d, vector<int>& worked, size_t worker){
//checks whether or not the worker is available on day d
  if(!avail[d][worker]) return false;

//check whether or not the worker has worked the max amount
  if(worked[worker]>=maxShifts) return false;

// check if the worker is already scheduled for a shift that day 
  if(find(sched[d].begin(), sched[d].end(), worker)!=sched[d].end()) return false;

  return true;
}



bool scheduler(const AvailabilityMatrix& avail, size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t d, size_t s, vector<int>& worked){
  //returns true if all days have been filled
  if(avail.size()==d)
    return true;

  size_t numWorker=avail[0].size();
  for(size_t w=0; w<numWorker; w++){
    if(canWork(avail, maxShifts, sched, d, worked, w)){
      sched[d].push_back(w);
      worked[w]++;

      if(sched[d].size()==dailyNeed){
        //recursive call to schedule the next days workflow
        if(sheduler(avail, dailyNeed, maxShift, sched, d+1, 0, worked)) return true;
      }
      else{
        //recursive call to schedule the next shift of the day
        if(sheduler(avail, dailyNeed, maxShift, sched, d, s+1, worked)) return true;
      }
      //backtracking if the scheduling doesnt work and prior info needs to change
      sched[d].pop_back();
      worked[w]--;
    }
  }
  return false;
}
