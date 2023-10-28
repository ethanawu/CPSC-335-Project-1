/*
    Pseudocode:
    Define the structure for an Employee
    Structure Employee:
        schedule: List of pairs of strings (start_time, end_time)
        working_period: Pair of strings (start_time, end_time)

// Function to convert a time string into minutes

// Function to convert minutes into a time string


// Function to find available meeting times
Function findAvailableMeetingTimes(employees, duration):
    common_working_start = Maximum of working start times of all employees
    common_working_end = Minimum of working end times of all employees
    available_slots = List containing a single pair (common_working_start, common_working_end)

    For each employee in employees:
        For each busy_slot in the employee's schedule:
            busy_start = Convert busy_slot.start_time to minutes
            busy_end = Convert busy_slot.end_time to minutes
            updated_available_slots = Empty List

            For each available_slot in available_slots:
                available_start = Convert available_slot.start_time to minutes
                available_end = Convert available_slot.end_time to minutes

                If busy_end <= available_start or busy_start >= available_end:
                    Add available_slot to updated_available_slots
                Else:
                    If busy_start > available_start:
                        Add a new slot (available_start, busy_start) to updated_available_slots
                    If busy_end < available_end:
                        Add a new slot (busy_end, available_end) to updated_available_slots

            available_slots = updated_available_slots

    result_slots = Empty List

    For each slot in available_slots:
        slot_start = Convert slot.start_time to minutes
        slot_end = Convert slot.end_time to minutes
        If (slot_end - slot_start) >= duration:
            Add slot to result_slots

    Return result_slots
    output: set availableMeetingTime[]
*/

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

//Structure of employees
struct Employee {
    vector<pair<string, string>> schedule;
    pair<string, string> working_period;
};

// convert time string into integer
int stringToMinutes(const string& timeString) {
    int hours, minutes;
    sscanf(timeString.c_str(), "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

//convert minutes back into time
string minutesToTime(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    return (hours < 10 ? "0" : "") + to_string(hours) + ":" + (mins < 10 ? "0" : "") + to_string(mins);
}


vector<pair<string, string>> findAvailableMeetingTimes(const vector<Employee>& employees, int duration) {
    //Get the best starttime sharred between the employees
    int start_time = max(stringToMinutes(employees[0].working_period.first), stringToMinutes(employees[1].working_period.first));
    int end_time = min(stringToMinutes(employees[0].working_period.second), stringToMinutes(employees[1].working_period.second));

    // set available slots as start and end time
    vector<pair<string, string>> availableSlots;
    availableSlots.push_back({minutesToTime(start_time), minutesToTime(end_time)});

    // Iterate over the schedules and remove busy slots
    for (const Employee& employee : employees) {
        for (const pair<string, string>& busySlot : employee.schedule) {
            int busy_start = stringToMinutes(busySlot.first);
            int busy_end = stringToMinutes(busySlot.second);
            vector<pair<string, string>> updatedAvailableSlots;

            for (const pair<string, string>& availableSlot : availableSlots) {
                int available_start = stringToMinutes(availableSlot.first);
                int available_end = stringToMinutes(availableSlot.second);

                if (busy_end <= available_start || busy_start >= available_end) {
                    updatedAvailableSlots.push_back(availableSlot);
                } else {
                    if (busy_start > available_start) {
                        updatedAvailableSlots.push_back({minutesToTime(available_start), minutesToTime(busy_start)});
                    }
                    if (busy_end < available_end) {
                        updatedAvailableSlots.push_back({minutesToTime(busy_end), minutesToTime(available_end)});
                    }
                }
            }
            availableSlots = updatedAvailableSlots;
        }
    }

    // Filter available slots that are at least 'duration' long
    vector<pair<string, string>> resultSlots;
    for (const pair<string, string>& slot : availableSlots) {
        int slot_start = stringToMinutes(slot.first);
        int slot_end = stringToMinutes(slot.second);
        if (slot_end - slot_start >= duration) {
            resultSlots.push_back(slot);
        }
    }

    return resultSlots;
}

int main() {
    Employee person1;
    Employee person2;
    person1.schedule = {{"7:00", "8:30"}, {"12:00", "13:00"}, {"16:00", "18:00"}};
    person1.working_period = {"9:00", "19:00"};
    person2.schedule = {{"9:00", "10:30"}, {"12:20", "13:30"}, {"14:00", "15:00"}, {"16:00", "17:00"}};
    person2.working_period = {"9:00", "18:30"};

    vector<Employee> employees = {person1, person2};

    int duration = 30;
    vector<pair<string, string>> availableMeetingTimes = findAvailableMeetingTimes(employees, duration);

    // Output the available meeting times
    for (const pair<string, string>& slot : availableMeetingTimes) {
        cout << "[" << slot.first << ", " << slot.second << "]" << endl;
    }

    return 0;
}