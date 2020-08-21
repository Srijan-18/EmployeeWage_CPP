#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

class Employee {
    public:
    string employeeName;
    int hoursWorkedToday;
    vector<int> dailyWage; 
    int monthlyWage;
    int totalWorkedDaysInAMonth;
    int totalWorkedHoursInAMonth;
    int numOfMonths;
   
    Employee(){}
    Employee(int maxNumOfDays)
    {
        this -> hoursWorkedToday = 0;
        this -> monthlyWage = 0;
        this -> totalWorkedDaysInAMonth = 0;
        this -> totalWorkedHoursInAMonth = 0;
        this -> dailyWage = vector<int>(maxNumOfDays);
        this -> numOfMonths = 0;
    }
};

const int IS_PRESENT_FULL_TIME = 1;
const int IS_PRESENT_PART_TIME = 2;
const int HOURS_IN_FULL_DAY = 8;
const int HOURS_IN_PART_TIME_DAY = 4;
const int WAGE_PER_HOUR = 20;
const int MAX_WORKING_DAYS_IN_A_MONTH = 20;
const int MAX_WORKING_HOURS_IN_MONTH = 100;

int getWorkingHours();
void writeInFile(string employeeName, string monthCount, string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage);
void getEmployeeNames(Employee employees[], int numOfEmployees);
int getNumberOfMonths();
Employee getUpdatedEmployeeInformation(int daysWorkedInPreviousMonth, Employee currentEmployee);

int main()
{
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    srand(time(0));
    remove("Data.csv");
    writeInFile("EMPLOYEE_NAME", "MONTH", "DAY", "HOURS_FOR_DAY", "WAGE_FOR_DAY", "CURRENT_MONTH_WAGE");
    const int MAX_NUM_OF_MONTHS = getNumberOfMonths();
    int numOfEmployees;
    cout << "Enter the number of employees: ";
    cin >> numOfEmployees;
    
    Employee *employees = new Employee[numOfEmployees];
        for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
            employees[employeeCount] = Employee(MAX_WORKING_DAYS_IN_A_MONTH * MAX_NUM_OF_MONTHS);
    
    getEmployeeNames(employees, numOfEmployees);
    
    for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
    {
        Employee currentEmployee = Employee(MAX_WORKING_DAYS_IN_A_MONTH * MAX_NUM_OF_MONTHS);
        currentEmployee.employeeName = employees[employeeCount].employeeName;
        while (currentEmployee.numOfMonths < MAX_NUM_OF_MONTHS)
        {
            int daysWorkedInPreviousMonth = currentEmployee.totalWorkedDaysInAMonth;
            currentEmployee.totalWorkedDaysInAMonth = 0;
            currentEmployee.monthlyWage = 0;
            currentEmployee.totalWorkedHoursInAMonth = 0;
            currentEmployee = getUpdatedEmployeeInformation(daysWorkedInPreviousMonth, currentEmployee);
        }
    }

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

void getEmployeeNames(Employee employees[], int numOfEmployees) {
    for(int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
    {
        cout << "Enter the Name of Employee Number " << employeeCount + 1 << " : ";
        cin >> employees[employeeCount].employeeName;
    }
}

int getNumberOfMonths(){
    int months;
    cout << "Enter Number Of Months To Calculate Wage For: ";
    cin >> months;
    return months;
}

Employee getUpdatedEmployeeInformation(int daysWorkedInPreviousMonth, Employee currentEmployee) 
{

    while (currentEmployee.totalWorkedDaysInAMonth < MAX_WORKING_DAYS_IN_A_MONTH && currentEmployee.totalWorkedHoursInAMonth < MAX_WORKING_HOURS_IN_MONTH)
            {
                currentEmployee.hoursWorkedToday = getWorkingHours();
                currentEmployee.dailyWage.at(daysWorkedInPreviousMonth + currentEmployee.totalWorkedDaysInAMonth) = currentEmployee.hoursWorkedToday * WAGE_PER_HOUR;
                currentEmployee.totalWorkedHoursInAMonth += currentEmployee.hoursWorkedToday;
                currentEmployee.monthlyWage += currentEmployee.dailyWage[(currentEmployee.totalWorkedDaysInAMonth)];
                writeInFile(currentEmployee.employeeName, to_string(currentEmployee.numOfMonths + 1), to_string(currentEmployee.totalWorkedDaysInAMonth + 1), to_string(currentEmployee.hoursWorkedToday), to_string(currentEmployee.dailyWage[daysWorkedInPreviousMonth + currentEmployee.totalWorkedDaysInAMonth]), to_string(currentEmployee.monthlyWage));
            (currentEmployee.totalWorkedDaysInAMonth)++;
            }
            currentEmployee.numOfMonths++;
            return currentEmployee;
}
void writeInFile(string employeeName, string monthCount, string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage)
{
    fstream fileStream;
    fileStream.open("Data.csv", ios::out | ios::app);
    if (fileStream.is_open())
    {
        fileStream << employeeName << ",";
        fileStream << monthCount << ",";
        fileStream << dayCount << ",";
        fileStream << hoursWorkedInDay << ",";
        fileStream << wageForDay << ",";
        fileStream << totalWage << endl;
    }
}