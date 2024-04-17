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
void createSchedule(size_t currentDay, bool& actualSched, vector<int>& currentShifts, const AvailabilityMatrix& avail, const size_t d, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
	//Creates a vector to hold the shifts
	vector<int> currentShifts;
	
	//Fill the shifts
	for(size_t i = 0; i < avail[0].size(); i ++){
			currentShifts.push_back(maxShifts);
	}

	for(size_t i = 0; i < avail.size(); i ++){
			sched.push_back(vector<Worker_T>());
	}

	//Boolean to check if current schedule is valid
	bool actualSched = false;

	//Calls the helper function that will find a valid schedule
	createSchedule(0, actualSched, currentShifts, avail, dailyNeed, sched);

	//returns true or false depending on if an actual schedule was found
	return actualSched;
}

//helper function to find a valid schedule
void createSchedule(size_t currentDay, bool& actualSched, vector<int>& currentShifts, const AvailabilityMatrix& avail, const size_t d, DailySchedule& sched){
	//Checks if a valid schedule has been found
	if(actualSched)
        return;
		
	//Checks the end of the available days have been reached
	else if(currentDay == avail.size()){
			actualSched = true;
			return;
	}

	//checks if there size of the schedule of the current date meets the daily needs
	else if(sched[currentDay].size() == d)
			createSchedule(currentDay + 1, actualSched, currentShifts, avail, d, sched);
	
	//Fills in space with employees
	else{
			Worker_T start;
			//Checks if the schedule of the current day is empty
			if (sched[currentDay].empty()) {
					start = 0;
			}
			else {
					start = sched[currentDay].back() + 1;
			}

			//Fills in the schedule
			for(Worker_T i = start; i < avail[currentDay].size(); i ++){
					if(avail[currentDay][i] && currentShifts[i] > 0){
							sched[currentDay].push_back(i);
							currentShifts[i] --;
							createSchedule(currentDay, actualSched, currentShifts, avail, d, sched);
							if(actualSched)
									return;
							sched[currentDay].pop_back();
							currentShifts[i]++;
					}
			}
	}
}