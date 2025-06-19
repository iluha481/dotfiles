#include <iostream>
#include <string>
#include <limits>

// Структура Date
struct Date {
    int day, month, year;
    void print() const {
        std::cout << day << "." << month << "." << year;
    }
};

// Перечисление для хранения типа сотрудника.
// Необходимо из-за требования без виртуальных функций.
enum EmployeeType {
    ET_EMPLOYEE, ET_MANAGER, ET_DEVELOPER
};

// Базовый класс Employee
class Employee {
protected:
    std::string name;
    int id;
    Date birthDate;
    double baseSalary; // Базовый оклад
    EmployeeType type; // Поле для определения типа объекта

public:
    Employee(std::string n, int i, Date bd, double bs)
        : name(n), id(i), birthDate(bd), baseSalary(bs), type(ET_EMPLOYEE) {}
    // Деструктор.
    ~Employee() {}

    // Геттеры
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getBaseSalary() const { return baseSalary; }
    EmployeeType getType() const { return type; }

    // Базовый метод расчета зарплаты
    double calculateSalary() const {
        return baseSalary;
    }

    // Метод вывода информации 
    void print() const {
        std::cout << "ID: " << id << ", Имя: " << name << ", Оклад: " << baseSalary;
    }
};

// Производные классы
// Класс Manager
class Manager : public Employee {
private:
    double departmentTurnover;
    double bonusPercentage;

public:
    Manager(std::string n, int i, Date bd, double bs, double turnover, double bonus)
        : Employee(n, i, bd, bs), departmentTurnover(turnover), bonusPercentage(bonus) {
        type = ET_MANAGER; // Устанавливаем тип
    }
    ~Manager() {}
    // Собственный расчет зарплаты
    double calculateSalary() const {
        return baseSalary + (departmentTurnover * bonusPercentage / 100.0);
    }
};

// Класс Developer
class Developer : public Employee {
public:
    Developer(std::string n, int i, Date bd, double fixedSalary)
        : Employee(n, i, bd, fixedSalary) {
        type = ET_DEVELOPER; // Устанавливаем тип
    }
    ~Developer() {}
    // У разработчика зарплата фиксированная и равна окладу
    double calculateSalary() const {
        return baseSalary; 
    }
};

// Класс для управления компанией
class Company {
private:
    Employee** employees; // Массив указателей на сотрудников
    int count;
    int capacity;

    void resize() {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        Employee** newEmployees = new Employee*[capacity];
        for (int i = 0; i < count; ++i) {
            newEmployees[i] = employees[i];
        }
        delete[] employees;
        employees = newEmployees;
    }

public:
    Company() : employees(nullptr), count(0), capacity(0) {}

    ~Company() {
        for (int i = 0; i < count; ++i) {
            delete employees[i]; // Освобождаем память для каждого объекта
        }
        delete[] employees; // Освобождаем память для массива указателей
    }

    void addEmployee(Employee* emp) {
        if (count == capacity) {
            resize();
        }
        employees[count++] = emp;
    }

    void removeEmployeeByIndex(int index) {
        if (index < 0 || index >= count) {
            std::cout << "Ошибка: неверный индекс." << std::endl;
            return;
        }
        delete employees[index]; 
        for (int i = index; i < count - 1; ++i) {
            employees[i] = employees[i + 1];
        }
        count--;
    }
    
    // Метод для получения зарплаты с учетом типа сотрудника
    double getEmployeeSalary(int index) const {
        Employee* emp = employees[index];
        // Проверяем тип и приводим указатель к нужному классу
        // нужно для вызова правильного метода, иначе вызовется базовый
        switch (emp->getType()) {
            case ET_MANAGER:
                // Приводим базовый указатель к указателю на Manager
                // static_cast нужен для приведения типа
                return static_cast<Manager*>(emp)->calculateSalary();
            case ET_DEVELOPER:
                // Приводим к указателю на Developer
                return static_cast<Developer*>(emp)->calculateSalary();
            default:
                return emp->calculateSalary();
        }
    }

    void printAllEmployees() const {
        std::cout << "\nСписок всех сотрудников" << std::endl;
        if (count == 0) {
            std::cout << "В компании нет сотрудников." << std::endl;
            return;
        }
        for (int i = 0; i < count; ++i) {
            employees[i]->print(); // Вызываем базовый метод print
            std::cout << ", Итоговая зарплата: " << getEmployeeSalary(i) << std::endl;
        }
    }

    void findMaxSalaryEmployee() const {
        if (count == 0) {
            std::cout << "В компании нет сотрудников для поиска." << std::endl;
            return;
        }
        int maxIndex = 0;
        double maxSalary = getEmployeeSalary(0);

        for (int i = 1; i < count; ++i) {
            double currentSalary = getEmployeeSalary(i);
            if (currentSalary > maxSalary) {
                maxSalary = currentSalary;
                maxIndex = i;
            }
        }
        std::cout << "\nСотрудник с максимальной зарплатой" << std::endl;
        employees[maxIndex]->print();
        std::cout << ", Итоговая зарплата: " << maxSalary << std::endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Company myCompany;
    
    // Создаем и добавляем сотрудников разных типов
    myCompany.addEmployee(new Developer("Иван Петров", 101, {10, 5, 1990}, 150000.0));
    myCompany.addEmployee(new Manager("Анна Сидорова", 202, {20, 8, 1985}, 120000.0, 5000000, 5.0));
    myCompany.addEmployee(new Developer("Олег Иванов", 102, {15, 3, 1995}, 180000.0));

    myCompany.printAllEmployees();

    myCompany.findMaxSalaryEmployee();

    std::cout << "\nУдаляем сотрудника с индексом 0" << std::endl;
    myCompany.removeEmployeeByIndex(0);

    myCompany.printAllEmployees();

    return 0; 
}