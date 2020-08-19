#include <iostream>
#include <ctime>

using namespace std;

const int IS_PRESENT = 1;
const int WAGE_PER_HOUR = 20;
const int HOURS_PER_FULL_DAY = 8;

int main()
{
    srand(time(0));
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    
    int employeeAttendance = rand() % 2;
    employeeAttendance == IS_PRESENT ? cout << "Employee Is Present" << endl : cout << "Employee Is Absent" << endl;
    
    int employeeWageForTheDay = WAGE_PER_HOUR * HOURS_PER_FULL_DAY * employeeAttendance;
    cout << "Wage for the day = " << employeeWageForTheDay << endl;

    return 0;
}