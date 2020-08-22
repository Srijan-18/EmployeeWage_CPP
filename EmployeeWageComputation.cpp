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
        this->companyName = name;
        this->employees = new Employee[numOfEmployees];
        this->wagePerHour = wagePerHour;
        this->maxWorkingDaysInAMonth = maxWorkingDaysInAMonth;
        this->maxWorkingHoursInAMonth = maxWorkingHoursInAMonth;
        this->balanceForCompany = 0;
    }
};

struct EmployeeInformation
{
    string companyName;
    string employeeName;
    int month;
    int day;
    int hoursForDay;
    int wageForDay;
    int monthlyWage;
};

int getWorkingHours();
void writeInFile(string, string, string, string, string, string, string, string);
void getEmployeeNames(Employee[], int);
int getNumberOfMonths();
Employee loadAndReturnUpdatedEmployeeInformation(int, int, CompanyDetails *);
int getTotalWageByCompanyName(vector<CompanyDetails>);
vector<EmployeeInformation> readFromFile();
void printDataOnBasisOfMonthlyWage(vector<EmployeeInformation>);
bool isPresent(vector<EmployeeInformation>, EmployeeInformation);
vector<EmployeeInformation> sortByMonthlyWageForGivenMonth(vector<EmployeeInformation>, int);
vector<EmployeeInformation> getDatawithUniqueNames(vector<EmployeeInformation>);
vector<EmployeeInformation> sortByDailyWageForGivenMonth(vector<EmployeeInformation>, int);
void printDataOnBasisOfMaxDailyWage(vector<EmployeeInformation>);
void printDataForParticularWagePerHour(vector<EmployeeInformation>, int);

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
        int maxDays, maxHours, wagePerHour, numOfEmployees, totalWage, givenMonth, givenWagePerHour;
        cout << "\nEnter Name Of The Company: ";
        cin >> name;
        cout << "\nEnter Wage Per Hour For " << name << " : ";
        cin >> wagePerHour;
        cout << "\nEnter Working Days Per Month For " << name << " : ";
        cin >> maxDays;
        cout << "\nEnter Working Hours Per Month For " << name << " : ";
        cin >> maxHours;
        const int MAX_NUM_OF_MONTHS = getNumberOfMonths();
        cout << "\nEnter The Number Of Employees: ";
        cin >> numOfEmployees;
        CompanyDetails company(name, wagePerHour, maxDays, maxHours, numOfEmployees);
        vector<EmployeeInformation> employeeInformation;

        for (int employeeCounter = 0; employeeCounter < numOfEmployees; employeeCounter++)
            company.employees[employeeCounter] = Employee(company.maxWorkingDaysInAMonth * MAX_NUM_OF_MONTHS, company.companyName);

        getEmployeeNames(company.employees, numOfEmployees);

        for (int employeeCount = 0; employeeCount < numOfEmployees; employeeCount++)
        {
            Employee currentEmployee = company.employees[employeeCount];
            while (currentEmployee.numOfMonths < MAX_NUM_OF_MONTHS)
            {
                int daysWorkedInPreviousMonth = currentEmployee.totalWorkedDaysInAMonth;
                currentEmployee.totalWorkedDaysInAMonth = 0;
                currentEmployee.monthlyWage = 0;
                currentEmployee.totalWorkedHoursInAMonth = 0;
                company.employees[employeeCount] = currentEmployee;
                currentEmployee = loadAndReturnUpdatedEmployeeInformation(daysWorkedInPreviousMonth, employeeCount, &company);
            }
        }
        companies.push_back(company);
    menu:
        cout << "\nEnter 1 To Add A New Company \nEnter 2 To Get Total Wages By Company Name \nEnter 3 To Sort By Monthly Wage.\nEnter 4 To Sort By Daily Wage." 
             << "\nEnter 5 To Search Employees With Particular Wage Per Hour.\nAny Other Key To Stop" << endl
             << "Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;
        case 2:
            totalWage = getTotalWageByCompanyName(companies);
            totalWage != -1 ? cout << "\nTotal Wage Is: " << totalWage << endl : cout << "\nNO SUCH COMPANY IN RECORDS" << endl;
            goto menu;
            break;
        case 3:
            cout << "\nEnter Month Number: ";
            cin >> givenMonth;
            employeeInformation = readFromFile();
            employeeInformation = sortByMonthlyWageForGivenMonth(employeeInformation, givenMonth);
            printDataOnBasisOfMonthlyWage(employeeInformation);
            goto menu;
        case 4:
            cout << "\nEnter Month Number: ";
            cin >> givenMonth;
            employeeInformation = readFromFile();
            employeeInformation = sortByDailyWageForGivenMonth(employeeInformation, givenMonth);
            printDataOnBasisOfMaxDailyWage(employeeInformation);
            goto menu;
        case 5:
            cout << "\nEnter Wage Per Hour: ";
            cin >> givenWagePerHour;
            employeeInformation = readFromFile();
            printDataForParticularWagePerHour(employeeInformation, givenWagePerHour);
            goto menu;    
        default:
            break;
        }
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
    for (int employeeCounter = 0; employeeCounter < numOfEmployees; employeeCounter++)
    {
        cout << "\nEnter the Name of Employee Number " << employeeCounter + 1 << " : ";
        cin >> employees[employeeCounter].employeeName;
    }
}

int getNumberOfMonths()
{
    int months;
    cout << "\nEnter Number Of Months To Calculate Wage For: ";
    cin >> months;
    return months;
}

Employee loadAndReturnUpdatedEmployeeInformation(int daysWorkedInPreviousMonth, int employeeCount, CompanyDetails *company)
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

int getTotalWageByCompanyName(vector<CompanyDetails> companies)
{
    string companyName;
    cout << "\nEnter the name of the company: ";
    cin >> companyName;
    int totalWage = -1;
    for (int companyCounter = 0; companyCounter < companies.size(); companyCounter++)
        if (companies[companyCounter].companyName.compare(companyName) == 0)
        {
            totalWage = companies[companyCounter].balanceForCompany;
            break;
        }
    return totalWage;
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

vector<EmployeeInformation> readFromFile()
{
    vector<EmployeeInformation> employeesInformation;
    fstream fileStream;
    string strTemp;
    fileStream.open("Data.csv", ios::in);
    getline(fileStream, strTemp);
    while (!fileStream.eof())
    {
        EmployeeInformation currentEmployee;
        getline(fileStream, currentEmployee.companyName, ',');
        getline(fileStream, currentEmployee.employeeName, ',');
        getline(fileStream, strTemp, ',');
        currentEmployee.month = stoi(strTemp);
        getline(fileStream, strTemp, ',');
        currentEmployee.day = stoi(strTemp);
        getline(fileStream, strTemp, ',');
        currentEmployee.hoursForDay = stoi(strTemp);
        getline(fileStream, strTemp, ',');
        currentEmployee.wageForDay = stoi(strTemp);
        getline(fileStream, strTemp, ',');
        currentEmployee.monthlyWage = stoi(strTemp);
        getline(fileStream, strTemp, '\n');
        employeesInformation.push_back(currentEmployee);
    }
    return employeesInformation;
}

vector<EmployeeInformation> sortByMonthlyWageForGivenMonth(vector<EmployeeInformation> employeesInformation, int givenMonth)
{
    bool changesMade = false;
    for (int bSortOuter = 0; bSortOuter < employeesInformation.size(); bSortOuter++)
    {
        for (int bSortInner = bSortOuter; bSortInner < employeesInformation.size(); bSortInner++)
            if (employeesInformation[bSortOuter].monthlyWage < employeesInformation[bSortInner].monthlyWage && employeesInformation[bSortInner].month == givenMonth)
            {
                swap(employeesInformation[bSortOuter], employeesInformation[bSortInner]);
                changesMade = true;
            }
    }

    if (!changesMade)
    {
        vector<EmployeeInformation> temp;
        return temp;
    }
    employeesInformation = getDatawithUniqueNames(employeesInformation);
    return employeesInformation;
}

bool isPresent(vector<EmployeeInformation> employeesInformationTemp, EmployeeInformation employee)
{
    bool isFound = false;
    int indexCounter;
    for (indexCounter = 0; indexCounter < employeesInformationTemp.size(); indexCounter++)
        if (employeesInformationTemp[indexCounter].employeeName == employee.employeeName)
            isFound = true;
    return isFound;
}

vector<EmployeeInformation> getDatawithUniqueNames(vector<EmployeeInformation> employees)
{
    vector<EmployeeInformation> employeesInformationTemp;
    for (int employeeCounter = 0; employeeCounter < employees.size(); employeeCounter++)
    {
        if (!isPresent(employeesInformationTemp, employees[employeeCounter]) && employees[employeeCounter].employeeName != "\0")
            employeesInformationTemp.push_back(employees[employeeCounter]);
    }
    return employeesInformationTemp;
}

void printDataOnBasisOfMonthlyWage(vector<EmployeeInformation> employeesInformation)
{
    if (employeesInformation.size() == 0)
    {
        cout << "\nNO RECORDS FOR ENTERED MONTH" << endl;
        return;
    }
    for (int employeeCounter = 0; employeeCounter < employeesInformation.size(); employeeCounter++)
        cout << "COMPANY NAME: " << employeesInformation[employeeCounter].companyName 
             << "\t\tEMPLOYE NAME : " << employeesInformation[employeeCounter].employeeName 
             << "\t\tMAX MONTHLY INCOME: " << employeesInformation[employeeCounter].monthlyWage << endl;
}

vector<EmployeeInformation> sortByDailyWageForGivenMonth(vector<EmployeeInformation> employeesInformation, int givenMonth)
{
    bool changesMade = false;
    for (int bSortOuter = 0; bSortOuter < employeesInformation.size(); bSortOuter++)
    {
        for (int bSortInner = bSortOuter; bSortInner < employeesInformation.size(); bSortInner++)
            if (employeesInformation[bSortOuter].wageForDay < employeesInformation[bSortInner].wageForDay && employeesInformation[bSortInner].month == givenMonth)
            {
                swap(employeesInformation[bSortOuter], employeesInformation[bSortInner]);
                changesMade = true;
            }
    }

    if (!changesMade)
    {
        vector<EmployeeInformation> temp;
        return temp;
    }
    employeesInformation = getDatawithUniqueNames(employeesInformation);
    return employeesInformation;
}

void printDataOnBasisOfMaxDailyWage(vector<EmployeeInformation> employeesInformation)
{
    if (employeesInformation.size() == 0)
    {
        cout << "\nNO RECORDS FOR ENTERED MONTH" << endl;
        return;
    }
    for (int employeeCounter = 0; employeeCounter < employeesInformation.size(); employeeCounter++)
        cout << "COMPANY NAME: " << employeesInformation[employeeCounter].companyName 
             << "\t\tEMPLOYE NAME : " << employeesInformation[employeeCounter].employeeName 
             << "\t\tMAX DAILY INCOME FOR GIVEN MONTH: " << employeesInformation[employeeCounter].wageForDay << endl;
}

void printDataForParticularWagePerHour(vector<EmployeeInformation> employeesInformation, int givenWage)
{
    vector<EmployeeInformation> employeesInformationTemp;
    for (int employeeCounter = 0; employeeCounter < employeesInformation.size(); employeeCounter++)
    {
        int wagePerHourForCurrentEmployee;
        employeesInformation[employeeCounter].wageForDay == 0 ? wagePerHourForCurrentEmployee = 0 : wagePerHourForCurrentEmployee = (employeesInformation[employeeCounter].wageForDay / employeesInformation[employeeCounter].hoursForDay);
        if (wagePerHourForCurrentEmployee == givenWage)
            employeesInformationTemp.push_back(employeesInformation[employeeCounter]);
    }
    if (employeesInformationTemp.size() == 0)
    {
        cout << "\n NO EMPLOYEE WITH SUCH WAGE PRESENT" << endl;
        return;
    }
    employeesInformationTemp = getDatawithUniqueNames(employeesInformationTemp);
    for (int employeeCount = 0; employeeCount < employeesInformationTemp.size(); employeeCount++)
        cout << "EMPLOYEE NAME: " << employeesInformationTemp[employeeCount].employeeName
             << "\t\tWAGE PER HOUR: " << employeesInformationTemp[employeeCount].wageForDay / employeesInformationTemp[employeeCount].hoursForDay
             << endl;
}