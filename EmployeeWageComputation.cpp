#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

struct Employee
{
    string companyName;
    string employeeName;
    int hoursWorkedToday;
    vector<int> dailyWage;
    int monthlyWage;
    int totalWorkedDaysInAMonth;
    int totalWorkedHoursInAMonth;
    int numOfMonths;

    Employee() {}
    Employee(int maxNumOfDays, string companyName)
    {
        this->companyName = companyName;
        this->hoursWorkedToday = 0;
        this->monthlyWage = 0;
        this->totalWorkedDaysInAMonth = 0;
        this->totalWorkedHoursInAMonth = 0;
        this->dailyWage = vector<int>(maxNumOfDays);
        this->numOfMonths = 0;
    }
};

struct CompanyDetails
{
    int wagePerHour;
    int maxWorkingDaysInAMonth;
    int maxWorkingHoursInAMonth;
    int balanceForCompany;
    string companyName;
    Employee *employees;
    CompanyDetails() {}

    CompanyDetails(string name, int wagePerHour, int maxWorkingDaysInAMonth, int maxWorkingHoursInAMonth, int numOfEmployees)
    {
        this -> companyName = name;
        this -> employees = new Employee[numOfEmployees];
        this -> wagePerHour = wagePerHour;
        this -> maxWorkingDaysInAMonth = maxWorkingDaysInAMonth;
        this -> maxWorkingHoursInAMonth = maxWorkingHoursInAMonth;
        this -> balanceForCompany = 0;
    }
};

int getWorkingHours();
void writeInFile(string, string, string, string, string, string, string, string);
void getEmployeeNames(Employee[], int);
int getNumberOfMonths();
Employee loadAndReturnUpdatedEmployeeInformation(int, int, CompanyDetails*);

int main()
{
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    srand(time(0));
    remove("Data.csv");
    writeInFile("COMPANY_NAME", "EMPLOYEE_NAME", "MONTH", "DAY", "HOURS_FOR_DAY", "WAGE_FOR_DAY", "CURRENT_MONTH_WAGE", "BALANCE_FOR_COMPANY");
    vector<CompanyDetails> companies;
    int choice = 1;
    while (choice == 1)
    {
        string name;
        int maxDays, maxHours, wagePerHour, numOfEmployees;
        cout << "Enter Name of the company: ";
        cin >> name;
        cout << "\nEnter Wage Per hour for " << name << " : ";
        cin >> wagePerHour;
        cout << "\nEnter Working Days Per Month for " << name << " : ";
        cin >> maxDays;
        cout << "\nEnter Working Hours Per Month for " << name << " : ";
        cin >> maxHours;
        const int MAX_NUM_OF_MONTHS = getNumberOfMonths();
        cout << "Enter the number of employees: ";
        cin >> numOfEmployees;
        CompanyDetails company(name, wagePerHour, maxDays, maxHours, numOfEmployees);
        
        for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
            company.employees[employeeCount] = Employee(company.maxWorkingDaysInAMonth * MAX_NUM_OF_MONTHS, company.companyName);

        getEmployeeNames(company.employees, numOfEmployees);

        for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
        {   
            cout << "COMPANY BALANCE IN MAIN --> " << company.balanceForCompany << endl;
            Employee currentEmployee = company.employees[employeeCount];
            while (currentEmployee.numOfMonths < MAX_NUM_OF_MONTHS)
            {
                int daysWorkedInPreviousMonth = currentEmployee.totalWorkedDaysInAMonth;
                currentEmployee.totalWorkedDaysInAMonth = 0;
                currentEmployee.monthlyWage = 0;
                currentEmployee.totalWorkedHoursInAMonth = 0;
                company.employees[employeeCount] = currentEmployee;
                currentEmployee = loadAndReturnUpdatedEmployeeInformation(daysWorkedInPreviousMonth, employeeCount, &company);
                cout << "COMPANY BALANCE IN MAIN AFTER A MONTH --> " << company.balanceForCompany << endl;
            }
        }
        companies.push_back(company);
        cout << "Enter 1 to add a new company , Any other key to stop" << endl
             << "Your Choice : ";
        cin >> choice;
    }
    return 0;
}

int getWorkingHours()
{
    const int IS_PRESENT_FULL_TIME = 1;
    const int IS_PRESENT_PART_TIME = 2;
    const int HOURS_IN_FULL_DAY = 8;
    const int HOURS_IN_PART_TIME_DAY = 4;
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

void getEmployeeNames(Employee employees[], int numOfEmployees)
{
    for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
    {
        cout << "Enter the Name of Employee Number " << employeeCount + 1 << " : ";
        cin >> employees[employeeCount].employeeName;
    }
}

int getNumberOfMonths()
{
    int months;
    cout << "Enter Number Of Months To Calculate Wage For: ";
    cin >> months;
    return months;
}

Employee loadAndReturnUpdatedEmployeeInformation(int daysWorkedInPreviousMonth, int employeeCount, CompanyDetails* company)
{
    Employee currentEmployee = (*company).employees[employeeCount];
    while (currentEmployee.totalWorkedDaysInAMonth < (*company).maxWorkingDaysInAMonth && currentEmployee.totalWorkedHoursInAMonth < (*company).maxWorkingHoursInAMonth)
    {
        currentEmployee.hoursWorkedToday = getWorkingHours();
        currentEmployee.dailyWage.at(daysWorkedInPreviousMonth + currentEmployee.totalWorkedDaysInAMonth) = currentEmployee.hoursWorkedToday * (*company).wagePerHour;
        currentEmployee.totalWorkedHoursInAMonth += currentEmployee.hoursWorkedToday;
        currentEmployee.monthlyWage += currentEmployee.dailyWage[(currentEmployee.totalWorkedDaysInAMonth)];
        (*company).balanceForCompany += currentEmployee.dailyWage[(currentEmployee.totalWorkedDaysInAMonth)];
        writeInFile(currentEmployee.companyName, currentEmployee.employeeName,
                    to_string(currentEmployee.numOfMonths + 1),
                    to_string(currentEmployee.totalWorkedDaysInAMonth + 1),
                    to_string(currentEmployee.hoursWorkedToday),
                    to_string(currentEmployee.dailyWage[daysWorkedInPreviousMonth + currentEmployee.totalWorkedDaysInAMonth]),
                    to_string(currentEmployee.monthlyWage),
                    to_string((*company).balanceForCompany));
        (currentEmployee.totalWorkedDaysInAMonth)++;
    }
    currentEmployee.numOfMonths++;
    (*company).employees[employeeCount] = currentEmployee;
    return currentEmployee;
}

void writeInFile(string companyName, string employeeName, string monthCount, string dayCount, string hoursWorkedInDay, string wageForDay, string totalWage, string balanceForCompany)
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
        fileStream << totalWage << ",";
        fileStream << balanceForCompany << endl;
    }
}