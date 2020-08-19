#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0)); 
    const int IS_PRESENT = 1;
    cout << "WELCOME TO EMPLOYEE WAGE COMPUTATION PROGRAM" << endl;
    int employeeAttendance = rand() % 2;
    employeeAttendance == IS_PRESENT ? cout << "Employee Is Present" << endl : cout << "Employee Is Absent"; 
}