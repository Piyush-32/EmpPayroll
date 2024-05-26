#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int id;

public:
    Employee(string name, int id) : name(name), id(id) {}

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    virtual double CalculateSalary() const = 0;

    virtual string toString() const {
        return "Employee[name=" + name + ", id=" + to_string(id) + ", salary=" + to_string(CalculateSalary()) + "]";
    }

    virtual ~Employee() {}  // Virtual destructor for proper cleanup
};

class FullTimeEmployee : public Employee {
private:
    double monthlySalary;

public:
    FullTimeEmployee(string name, int id, double monthlySalary) 
        : Employee(name, id), monthlySalary(monthlySalary) {}

    double CalculateSalary() const override {
        return monthlySalary;
    }

    string toString() const override {
        return "FullTimeEmployee[name=" + name + ", id=" + to_string(id) + ", salary=" + to_string(CalculateSalary()) + "]";
    }
};

class PartTimeEmployee : public Employee {
private:
    int hoursWorked;
    double hourlyRate;

public:
    PartTimeEmployee(string name, int id, int hoursWorked, double hourlyRate) 
        : Employee(name, id), hoursWorked(hoursWorked), hourlyRate(hourlyRate) {}

    double CalculateSalary() const override {
        return hoursWorked * hourlyRate;
    }

    string toString() const override {
        return "PartTimeEmployee[name=" + name + ", id=" + to_string(id) + ", salary=" + to_string(CalculateSalary()) + "]";
    }
};

class Payroll {
private:
    vector<Employee*> employees;

public:
    ~Payroll() {
        for (Employee* emp : employees) {
            delete emp;
        }
    }

    void addEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    void removeEmployee(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;  // Free the memory
                employees.erase(it);
                break;
            }
        }
    }

    void displayEmployees() const {
        for (const Employee* emp : employees) {
            cout << emp->toString() << endl;
        }
    }
};

void addFullTimeEmployee(Payroll& payroll) {
    string name;
    int id;
    double monthlySalary;

    cout << "Enter Full-Time Employee Name: ";
    cin >> name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Monthly Salary: ";
    cin >> monthlySalary;

    payroll.addEmployee(new FullTimeEmployee(name, id, monthlySalary));
}

void addPartTimeEmployee(Payroll& payroll) {
    string name;
    int id;
    int hoursWorked;
    double hourlyRate;

    cout << "Enter Part-Time Employee Name: ";
    cin >> name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Hours Worked: ";
    cin >> hoursWorked;
    cout << "Enter Hourly Rate: ";
    cin >> hourlyRate;

    payroll.addEmployee(new PartTimeEmployee(name, id, hoursWorked, hourlyRate));
}

void removeEmployee(Payroll& payroll) {
    int id;
    cout << "Enter Employee ID to Remove: ";
    cin >> id;
    payroll.removeEmployee(id);
}

int main() {
    Payroll payroll;
    int choice;

    while (true) {
        cout << "\nPayroll System Menu\n";
        cout << "1. Add Full-Time Employee\n";
        cout << "2. Add Part-Time Employee\n";
        cout << "3. Display All Employees\n";
        cout << "4. Remove Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addFullTimeEmployee(payroll);
                break;
            case 2:
                addPartTimeEmployee(payroll);
                break;
            case 3:
                payroll.displayEmployees();
                break;
            case 4:
                removeEmployee(payroll);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
