#include <algorithm>
#include <vector>
#include <string>

bool isEven(int value)
{
    return ((value % 2) == 0);
}
// Helper function to check if all even numbers are before odd numbers
//Uses std::partition to rearrange the list so that all even numbers come before all odd numbers.
void partitionEvenOdd(std::vector<int>& numbers) {
    std::stable_partition(numbers.begin(), numbers.end(), isEven);
}

// You are tasked with processing a list of patients in a hospital emergency room.
// Each patient has:
//  • A name (string)
//  • An arrival time (integer timestamp)
//  • A severity level (integer from 1 to 5, where 1 is the most severe)
//
// Your goal is to prioritize patients for treatment based on their severity levels.
// Specifically, you need to:
//  1. Rearrange the list of patients so that all patients with a severity level of
//  1 or 2 are moved to the front of the list (higher priority), and patients with
//  severity levels 3, 4, or 5 are moved to the back (lower priority).
//  2. Within each priority group, patients must be ordered by their arrival time,
//  maintaining the original arrival order. That is, among patients with severity
//  levels 1 or 2, those who arrived earlier should come first.
//  3. Process (e.g., print out) the patients in the new order.
//
// Constraints and Requirements:
//
//  • Data Structures:
//  • Define a Patient struct or class with the necessary fields.
//  • Store patients in a std::vector<Patient>.
//  • Input:
//  • Read a list of patients from the user or a predefined data set.
//  Each patient entry should include their name, arrival time, and severity level.
//  • Processing:
//  • Rearrange the patient list according to the severity level and arrival time criteria.
//  • Output:
//  • Print the rearranged list of patients, showing their names, arrival times, and severity levels.
//
// Example:
//
// Suppose you have the following list of patients (in order of arrival):
//  1. Alice - Arrival Time: 1 - Severity Level: 3
//  2. Bob - Arrival Time: 2 - Severity Level: 2
//  3. Charlie - Arrival Time: 3 - Severity Level: 1
//  4. Diana - Arrival Time: 4 - Severity Level: 4
//  5. Ethan - Arrival Time: 5 - Severity Level: 2
//  6. Fiona - Arrival Time: 6 - Severity Level: 5
//

struct Patient {
    Patient(const std::string& name, const int arrival_time, const int severity_level)
        : name(name)
          , arrival_time(arrival_time)
          , severity_level(severity_level)
    {}

    std::string name;
    int arrival_time;
    int severity_level;
};


void rearrangePatients(std::vector<Patient>& patients)
{
    auto comp = [](const Patient& left, const Patient& right)->bool {
        return (left.arrival_time<right.arrival_time);
    };

    std::sort(patients.begin(), patients.end(), comp);

    std::stable_partition(patients.begin(), patients.end(), [](const Patient& p)->bool {
        return (p.severity_level < 3);
            });


}
