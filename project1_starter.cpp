/*
    Pseudocode:
    Global:
        busyTime

    int timeValue (input string timeString)
        string newString = timeString
        my_str.erase(remove(my_str.begin(), my_str.end(), ':'), my_str.end()); //omit the colon
        stoi //turn into an integer
        return timeValue

    //Greedy Method
    matchingGroupSced(input vector<pair> Busy_Schedule[], vector<pair> Working_period[])
        



    output: set availableMeetingTime[]
*/

using namespace std;

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <vector>

struct Employee{
    vector<pair<string, string>> scheduele; 
    pair<string, string> working_period;
}; 

//Extract Value 
int stringToTime(string timeString) {
    int newString = 0;
    timeString.erase(remove(timeString.begin(), timeString.end(), ':'), timeString.end());
    newString = stoi(timeString);
    return newString;
}

// Function to convert minutes to time string
string minutesToTime(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    return (hours < 10 ? "0" : "") + to_string(hours) + ":" + (mins < 10 ? "0" : "") + to_string(mins);
}

/*vector<pair<int, int>>*/ void matchingGroupSched(vector<Employee> employees) {
    
    cout << "First Employee's First Schedule: " << employees[0].scheduele[1].first << " - " << employees[0].scheduele[1].second << endl;
    cout << "into intergers" << stringToTime(employees[0].scheduele[0].first);
    for(int i = 0; i < employees.size(); i++) {
        for(int j = 0; j < employees[i].scheduele.size(); j++) {
            cout << "s";
        }
    }
    return;
}


int main() {
    
    vector<Employee> employees;
    Employee person1;
    Employee person2;
    person1.scheduele = {{"7:00", "8:30"}, {"12:00", "13:00"}, {"16:00", "18:00"}};
    person1.working_period = {"9:00", "19:00"};
    person2.scheduele = {{"9:00", "10:30"}, {"12:20", "13:30"}, {"14:00", "15:00"}, {"16:00", "17:00"}};
    person2.working_period = {"9:00", "18:30"};

    employees.push_back(person1);
    employees.push_back(person2);
    matchingGroupSched(employees);
    
    return 0;
}

