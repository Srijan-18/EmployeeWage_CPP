#include <iostream>
#include <ctime>

using namespace std;

const int IS_PRESENT_FULL_TIME = 1;
const int IS_PRESENT_PART_TIME = 2;
const int HOURS_IN_FULL_DAY = 8;
const int HOURS_IN_PART_TIME_DAY = 4;
const int WAGE_PER_HOUR = 20;

int getWorkingHours();

int main()
{
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;

    int employeeWageForTheDay = WAGE_PER_HOUR * getWorkingHours();
    cout << "Wage for the day = " << employeeWageForTheDay << endl;

    return 0;
}

int getWorkingHours()
{
    srand(time(0));
    int employeeAttendance = rand() % 3;
    switch (employeeAttendance)
    {
    case IS_PRESENT_FULL_TIME:
        cout << "Employee is Present Full Time" << endl;
        return HOURS_IN_FULL_DAY;
    case IS_PRESENT_PART_TIME:
        cout << "Employee is Present Part Time" << endl;
        return HOURS_IN_PART_TIME_DAY;
    default:
        cout << "Employee is Absent" << endl;
        return 0;
    }
}