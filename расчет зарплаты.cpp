#include <iostream>
using namespace std;
class Employee {
protected:
    string firstName;
    string lastName;

public:
    Employee(const string& first, const string& last)
            : firstName(first), lastName(last) {}

    virtual double calculateSalary() const = 0;
    virtual void display() const = 0;

    virtual ~Employee() {}
};

class Worker : public Employee {
private:
    double hoursNumber;
    double hourlyRate;

public:
    Worker(const string& first, const string& last, double hours, double rate)
            : Employee(first, last), hoursNumber(hours), hourlyRate(rate) {}

    double calculateSalary() const override {
        double salary = hoursNumber * hourlyRate;
        if (hoursNumber > 40) {
            salary += (hoursNumber - 40) * hourlyRate;
        }
        return salary;
    }

    void display() const override {
        cout << firstName << " " << lastName << "\n"
                  << "hours number: " << hoursNumber << ", hourly rate: " << hourlyRate
                  << ", month salary: " << calculateSalary() << "\n";
    }
};

class SalaryWorker : public Employee {
protected:
    double salary;
    double bonus;

public:
    SalaryWorker(const string& first, const string& last, double s, double b)
            : Employee(first, last), salary(s), bonus(b) {}

    virtual double calculateBonus() const = 0;

    double calculateSalary() const override {
        return salary + calculateBonus();
    }

    void display() const override {
        cout << firstName << " " << lastName << "\n"
                  << "salary: " << salary << ", bonus: " << bonus
                  << ", month salary: " << calculateSalary() << "\n";
    }
};

class Salesman : public SalaryWorker {
private:
    double planPercentage;

public:
    Salesman(const string& first, const string& last, double s, double b, double plan)
            : SalaryWorker(first, last, s, b), planPercentage(plan) {}

    double calculateBonus() const override {
        return bonus * planPercentage / 100.0;
    }

    void display() const override {
        cout << firstName << " " << lastName << "\n"
                  << "salary: " << salary << ", bonus: " << bonus
                  << ", plan percentage: " << planPercentage
                  << ", month salary: " << calculateSalary() << "\n";
    }
};

class Manager : public SalaryWorker {
private:
    int clientCount;

public:
    Manager(const string& first, const string& last, double s, double b, int clients)
            : SalaryWorker(first, last, s, b), clientCount(clients) {}

    double calculateBonus() const override {
        double bonusMultiplier = 1.0;
        if (clientCount > 100) {
            bonusMultiplier *= 2.0;
        }
        if (clientCount > 200) {
            bonusMultiplier *= 3.0;
        }
        return bonus * bonusMultiplier;
    }

    void display() const override {
        cout << firstName << " " << lastName << "\n"
                  << "salary: " << salary << ", bonus: " << bonus
                  << ", clients count: " << clientCount
                  << ", month salary: " << calculateSalary() << "\n";
    }
};

int main() {
    Employee* employees[7];
    employees[0] = new Worker("Kate", "Jordan", 30, 10);
    employees[1] = new Worker("Jack", "Peterson", 50, 10);
    employees[2] = new Salesman("Peter", "Brown", 800, 100, 80);
    employees[3] = new Salesman("Antony", "Norton", 1000, 100, 150);
    employees[4] = new Manager("David", "Flynn", 2000, 200, 50);
    employees[5] = new Manager("Marian", "Wood", 1800, 200, 120);
    employees[6] = new Manager("Brent", "Simpson", 2200, 200, 250);

    for (int i = 0; i < 7; ++i) {
        employees[i]->display();
        cout << "\n";
    }

    for (int i = 0; i < 7; ++i) {
        delete employees[i];
    }

    return 0;
}
