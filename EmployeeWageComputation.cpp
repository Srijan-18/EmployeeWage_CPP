#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

const int IS_PRESENT_FULL_TIME = 1;
const int IS_PRESENT_PART_TIME = 2;
const int HOURS_IN_FULL_DAY = 8;
const int HOURS_IN_PART_TIME_DAY = 4;
const int WAGE_PER_HOUR = 20;
const int MAX_WORKING_DAYS_IN_A_MONTH = 20;
const int MAX_WORKING_HOURS_IN_MONTH = 100;

int getWorkingHours();
void writeInFile(string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage);

int main()
{
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    srand(time(0));
    int monthlyWage = 0, workingDays = 0, workingHours = 0;
    writeInFile("DAY", "HOURS_FOR_DAY", "WAGE_FOR_DAY", "TOTAL_WAGE");
    while (workingDays < MAX_WORKING_DAYS_IN_A_MONTH && workingHours < MAX_WORKING_HOURS_IN_MONTH)
    {
        int workingHourForToday = getWorkingHours();
        int wageForToday = workingHourForToday * WAGE_PER_HOUR;
        workingHours += workingHourForToday;
        monthlyWage += wageForToday;
        workingDays++;
        writeInFile(to_string(workingDays), to_string(workingHourForToday), to_string(wageForToday), to_string(monthlyWage));
    }
    cout << "Working Days --> " << workingDays << endl;
    cout << "Working Hours --> " << workingHours << endl;
    cout << "WAGE FOR THE MONTH --> " << monthlyWage << endl;

    return 0;
}

int getWorkingHours()
{
    int employeeAttendance = rand() % 3;
    switch (employeeAttendance)
    {
    case IS_PRESENT_FULL_TIME:
        return HOURS_IN_FULL_DAY;
    case IS_PRESENT_PART_TIME:
        return HOURS_IN_PART_TIME_DAY;
    default:
        return 0;
    }
}

void writeInFile(string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage)
{
    fstream fileStream;
    fileStream.open("Data.csv", ios::out | ios::app);
    if (fileStream.is_open())
    {
        fileStream << dayCount << ",";
        fileStream << hoursWorkedInDay << ",";
        fileStream << wageForDay << ",";
        fileStream << totalWage << endl;
    }
}