#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

struct Employee {
    public:
    string companyName;
    string employeeName;
    int hoursWorkedToday;
    vector<int> dailyWage; 
    int monthlyWage;
    int totalWorkedDaysInAMonth;
    int totalWorkedHoursInAMonth;
    int numOfMonths;
   
    Employee(){}
    Employee(int maxNumOfDays, string companyName)
    {
        this -> companyName = companyName;
        this -> hoursWorkedToday = 0;
        this -> monthlyWage = 0;
        this -> totalWorkedDaysInAMonth = 0;
        this -> totalWorkedHoursInAMonth = 0;
        this -> dailyWage = vector<int>(maxNumOfDays);
        this -> numOfMonths = 0;
    }
};

struct CompanyDetails{
    int wagePerHour;
    int maxWorkingDaysInAMonth;
    int maxWorkingHoursInAMonth;
    string companyName;
    CompanyDetails() {}

    CompanyDetails(int wagePerHour, int maxWorkingDaysInAMonth, int maxWorkingHoursInAMonth)
    {
        this -> wagePerHour = wagePerHour;
        this -> maxWorkingDaysInAMonth = maxWorkingDaysInAMonth;
        this -> maxWorkingHoursInAMonth = maxWorkingHoursInAMonth;    
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
void writeInFile(string, string, string, string, string, string, string);
void getEmployeeNames(Employee[], int);
int getNumberOfMonths();
Employee loadAndReturnUpdatedEmployeeInformation(int, Employee, CompanyDetails);

int main()
{
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    srand(time(0));
    remove("Data.csv");
    writeInFile("COMPANY_NAME", "EMPLOYEE_NAME", "MONTH", "DAY", "HOURS_FOR_DAY", "WAGE_FOR_DAY", "CURRENT_MONTH_WAGE");
    
    int choice = 1;
    while(choice == 1){
        CompanyDetails company;
        cout << "Enter Name of the company: ";
        cin >> company.companyName;
        cout << "\nEnter Wage Per hour for " << company.companyName << " : ";
        cin >> company.wagePerHour;
        cout << "\nEnter Working Days Per Month for " << company.companyName << " : ";
        cin >> company.maxWorkingDaysInAMonth;
        cout << "\nEnter Working Hours Per Month for " << company.companyName << " : ";
        cin >> company.maxWorkingHoursInAMonth;

        const int MAX_NUM_OF_MONTHS = getNumberOfMonths();
        int numOfEmployees;
        cout << "Enter the number of employees: ";
        cin >> numOfEmployees;
        
        Employee *employees = new Employee[numOfEmployees];
            for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
                employees[employeeCount] = Employee(company.maxWorkingDaysInAMonth * MAX_NUM_OF_MONTHS, company.companyName);
        
        getEmployeeNames(employees, numOfEmployees);
        
        for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
        {
            Employee currentEmployee = Employee(company.maxWorkingDaysInAMonth * MAX_NUM_OF_MONTHS, company.companyName);
            currentEmployee.employeeName = employees[employeeCount].employeeName;
            while (currentEmployee.numOfMonths < MAX_NUM_OF_MONTHS)
            {
                int daysWorkedInPreviousMonth = currentEmployee.totalWorkedDaysInAMonth;
                currentEmployee.totalWorkedDaysInAMonth = 0;
                currentEmployee.monthlyWage = 0;
                currentEmployee.totalWorkedHoursInAMonth = 0;
                currentEmployee = loadAndReturnUpdatedEmployeeInformation(daysWorkedInPreviousMonth, currentEmployee, company);
            }
        }
        cout << "Enter 1 to add a new company , Any other key to stop" << endl << "Your Choice : ";
        cin >> choice;
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

Employee loadAndReturnUpdatedEmployeeInformation(int daysWorkedInPreviousMonth, Employee currentEmployee, CompanyDetails company) 
{

    while (currentEmployee.totalWorkedDaysInAMonth < company.maxWorkingDaysInAMonth && currentEmployee.totalWorkedHoursInAMonth < company.maxWorkingHoursInAMonth)
            {
                currentEmployee.hoursWorkedToday = getWorkingHours();
                currentEmployee.dailyWage.at(daysWorkedInPreviousMonth + currentEmployee.totalWorkedDaysInAMonth) = currentEmployee.hoursWorkedToday * company.wagePerHour;
                currentEmployee.totalWorkedHoursInAMonth += currentEmployee.hoursWorkedToday;
                currentEmployee.monthlyWage += currentEmployee.dailyWage[(currentEmployee.totalWorkedDaysInAMonth)];
                writeInFile(currentEmployee.companyName, currentEmployee.employeeName, to_string(currentEmployee.numOfMonths + 1), to_string(currentEmployee.totalWorkedDaysInAMonth + 1), to_string(currentEmployee.hoursWorkedToday), to_string(currentEmployee.dailyWage[daysWorkedInPreviousMonth + currentEmployee.totalWorkedDaysInAMonth]), to_string(currentEmployee.monthlyWage));
            (currentEmployee.totalWorkedDaysInAMonth)++;
            }
            currentEmployee.numOfMonths++;
            return currentEmployee;
}
void writeInFile(string companyName, string employeeName, string monthCount, string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage)
{
    fstream fileStream;
    fileStream.open("Data.csv", ios::out | ios::app);
    if (fileStream.is_open())
    {
        fileStream << companyName << ",";
        fileStream << employeeName << ",";
        fileStream << monthCount << ",";
        fileStream << dayCount << ",";
        fileStream << hoursWorkedInDay << ",";
        fileStream << wageForDay << ",";
        fileStream << totalWage << endl;
    }
}