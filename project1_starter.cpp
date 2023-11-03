/*
    Pseudocode:
    Define the structure for an Employee
    Structure Employee:
        schedule: List of pairs of strings (start_time, end_time)
        working_period: Pair of strings (start_time, end_time)

// Function to convert a time string into minutes

// Function to convert minutes into a time string


// Function to find available meeting times
Function matchingGroupSched(employees, duration):
    Iterate over all employees to find the latest start time and the earliest end time
    
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
#include <sstream>
#include <fstream>

struct Employee {
    vector<pair<string, string>> schedule;
    pair<string, string> working_period;
};

int stringToMinutes(const string& timeString) {
    int hours, minutes;
    sscanf(timeString.c_str(), "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

string minutesToTime(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    return (hours < 10 ? "0" : "") + to_string(hours) + ":" + (mins < 10 ? "0" : "") + to_string(mins);
}


vector<pair<string, string>> matchingGroupSched(const vector<Employee>& employees, int duration) {
    
    int start_time = 0;  
    int end_time = 24 * 60;  
    
    
    for (const Employee& employee : employees) {
        start_time = max(start_time, stringToMinutes(employee.working_period.first));
        end_time = min(end_time, stringToMinutes(employee.working_period.second));
    }
    
    vector<pair<string, string>> availableSlots;
    availableSlots.push_back({minutesToTime(start_time), minutesToTime(end_time)});

    
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
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open input.txt" << endl;
        return 1;
    }

    int numEmployees;
    inputFile >> numEmployees;
    vector<Employee> employees(numEmployees);

    for (int i = 0; i < numEmployees; i++) {
        int numSlots;
        inputFile >> numSlots;
        for (int j = 0; j < numSlots; j++) {
            string start, end;
            inputFile >> start >> end;
            employees[i].schedule.push_back({start, end});
        }
        string workingStart, workingEnd;
        inputFile >> workingStart >> workingEnd;
        employees[i].working_period = {workingStart, workingEnd};
    }

    int duration;
    inputFile >> duration;

    vector<pair<string, string>> availableMeetingTimes = matchingGroupSched(employees, duration);

    // Output the available meeting times to output.txt
    for (const pair<string, string>& slot : availableMeetingTimes) {
        outputFile << "[" << slot.first << ", " << slot.second << "]" << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
