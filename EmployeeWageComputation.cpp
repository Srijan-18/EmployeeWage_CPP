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
    int totalWorkingDays;
    int totalWorkingHours;
   
    Employee(){}
    Employee(int maxNumOfDays)
    {
        this -> hoursWorkedToday = 0;
        this -> monthlyWage = 0;
        this -> totalWorkingDays = 0;
        this -> totalWorkingHours = 0;
        this -> dailyWage = vector<int>(maxNumOfDays);
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
void writeInFile(string employeeName, string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage);
void getEmployeeNames(Employee employees[], int numOfEmployees);

int main()
{
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    srand(time(0));
 //   int monthlyWage = 0, workingDays = 0, workingHours = 0;
    remove("Data.csv");
    writeInFile("EMPLOYEE_NAME","DAY", "HOURS_FOR_DAY", "WAGE_FOR_DAY", "TOTAL_WAGE");
    int numOfEmployees;
    cout << "Enter the number of employees: ";
    cin >> numOfEmployees;
    
    Employee *employees = new Employee[numOfEmployees];
        for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
        {
            employees[employeeCount] = Employee(MAX_WORKING_DAYS_IN_A_MONTH);
        }
    getEmployeeNames(employees, numOfEmployees);
    for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
    {
        Employee currentEmployee = Employee(MAX_WORKING_DAYS_IN_A_MONTH);
        currentEmployee.employeeName = employees[employeeCount].employeeName;
        //employees[employeeCount];
        while (currentEmployee.totalWorkingDays < MAX_WORKING_DAYS_IN_A_MONTH && currentEmployee.totalWorkingHours < MAX_WORKING_HOURS_IN_MONTH)
        {
            currentEmployee.hoursWorkedToday = getWorkingHours();
    //        cout << employees[employeeCount].hoursWorkedToday << "--" ;
            currentEmployee.dailyWage.at(currentEmployee.totalWorkingDays) = currentEmployee.hoursWorkedToday * WAGE_PER_HOUR;
  //          cout << employees[employeeCount].dailyWage.at(employees[employeeCount].totalWorkingDays) << "--";
            currentEmployee.totalWorkingHours += employees[employeeCount].hoursWorkedToday;
//            cout << employees[employeeCount].totalWorkingHours << "--";
            currentEmployee.monthlyWage += currentEmployee.dailyWage[(currentEmployee.totalWorkingDays)];
            cout << currentEmployee.dailyWage.at((currentEmployee.totalWorkingDays)) << endl;
            writeInFile(currentEmployee.employeeName, to_string(currentEmployee.totalWorkingDays + 1), to_string(currentEmployee.hoursWorkedToday), to_string(currentEmployee.dailyWage[currentEmployee.totalWorkingDays]), to_string(currentEmployee.monthlyWage));
           (currentEmployee.totalWorkingDays)++;
        }
        employees[employeeCount] = currentEmployee;
    }
    // cout << "Working Days --> " << workingDays << endl;
    // cout << "Working Hours --> " << workingHours << endl;
    // cout << "WAGE FOR THE MONTH --> " << monthlyWage << endl;

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
        cout << "Enter the Name of Emloyee Number " << employeeCount + 1 << " : ";
        cin >> employees[employeeCount].employeeName;
    }
}

void writeInFile(string employeeName, string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage)
{
    fstream fileStream;
    fileStream.open("Data.csv", ios::out | ios::app);
    if (fileStream.is_open())
    {
        fileStream << employeeName << ",";
        fileStream << dayCount << ",";
        fileStream << hoursWorkedInDay << ",";
        fileStream << wageForDay << ",";
        fileStream << totalWage << endl;
    }
}