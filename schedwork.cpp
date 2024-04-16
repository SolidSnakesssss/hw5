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
bool isValid(const std::vector<Worker_T>& daySchedule, size_t maxShifts, const std::vector<size_t>& shiftsCount);
bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
                    DailySchedule& sched, std::vector<size_t>& shiftsCount, size_t day, size_t workerIndex);

// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    size_t n = avail.size();
    size_t k = avail[0].size();

    // Initialize the schedule
    sched.resize(n);
    for (size_t i = 0; i < n; ++i) {
        sched[i].reserve(dailyNeed);
    }

    // Track the number of shifts for each worker
    std::vector<size_t> shiftsCount(k, 0);

    // Start backtracking from the first day
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, 0, 0);
}

bool isValid(const std::vector<Worker_T>& daySchedule, size_t maxShifts, const std::vector<size_t>& shiftsCount) {
    for (Worker_T worker : daySchedule) {
        if (shiftsCount[worker] >= maxShifts) {
            return false;
        }
    }
    return true;
}

bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
                    DailySchedule& sched, std::vector<size_t>& shiftsCount, size_t day, size_t workerIndex) {
    size_t n = avail.size();
    size_t k = avail[0].size();

    // Base case: all days are scheduled
    if (day == n) {
        return true;
    }

    // Base case: all workers have been tried for the current day
    if (workerIndex == k) {
        return false;
    }

    // Try assigning current worker to the current day
    sched[day].push_back(workerIndex);
    shiftsCount[workerIndex]++;
    if (isValid(sched[day], maxShifts, shiftsCount)) {
        // If valid, proceed to the next day
        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, day + 1, 0)) {
            return true;
        }
    }
    // Backtrack: remove the current worker from the current day
    sched[day].pop_back();
    shiftsCount[workerIndex]--;
    
    // Try the next worker for the current day
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, day, workerIndex + 1);
}