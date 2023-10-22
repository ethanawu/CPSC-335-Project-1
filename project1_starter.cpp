/*
    Pseudocode:
    int timeValue (input string timeString)
        string newString = timeString
        my_str.erase(remove(my_str.begin(), my_str.end(), ':'), my_str.end()); //omit the colon
        stoi //turn into an integer
        return timeValue

    matchingGroupSced(input Busy_Schedule[] Working_period[])
        



    output: set availableMeetingTime[]
*/

using namespace std;

#include <iostream>
#include <set>
#include <string>
#include <algorithm>

//Extract Value 
int stringToTime(string timeString) {
    int newString = 0;
    timeString.erase(remove(timeString.begin(), timeString.end(), ':'), timeString.end());
    newString = stoi(timeString);
    return newString;
}

/*
void matchingGroupSched(string a[][2], string Working_period[]) {

}
*/

int main() {
    
    return 0;
}