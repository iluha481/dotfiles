#include <iostream>
#include <string>
#include <limits> // Для std::numeric_limits

// Класс для представления автомобиля
class Car {
private:
    std::string brand;
    std::string model;
    int year;
    int mileage;

public:
    // Конструктор по умолчанию и с параметрами
    Car(std::string b = "", std::string m = "", int y = 2000, int mi = 0)
        : brand(b), model(m), year(y), mileage(mi) {}

    // Геттеры (методы для получения значений)
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    int getMileage() const { return mileage; }

    // Сеттеры (методы для установки значений)
    void setBrand(const std::string& b) { brand = b; }
    void setModel(const std::string& m) { model = m; }
    void setYear(int y) { year = y; }
    void setMileage(int mi) { mileage = mi; }

    // Метод для вывода информации об автомобиле
    void print() const {
        std::cout << "Марка: " << brand << std::endl;
        std::cout << "Модель: " << model << std::endl;
        std::cout << "Год выпуска: " << year << std::endl;
        std::cout << "Пробег: " << mileage << " км" << std::endl;
    }
};

// Функция для ввода целочисленного значения
int getIntegerInput() {
    int value;
    std::cin >> value;
    while (std::cin.fail() || value < 0) {
        std::cout << "Ошибка. Введите корректное положительное число: ";
        std::cin.clear();
        std::cin.ignore();
        std::cin >> value;
    }
    std::cin.ignore(); // Очистка буфера
    return value;
}


int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите количество автомобилей (N): ";
    int n = getIntegerInput();

    // Динамически выделяем массив из N объектов класса Car
    Car* cars = new Car[n];

    // Заполняем массив данными от пользователя
    for (int i = 0; i < n; ++i) {
        std::string brand, model;
        int year, mileage;

        std::cout << "\nВведите данные для автомобиля #" << i + 1 << ":" << std::endl;

        std::cout << "Марка: ";
        std::getline(std::cin, brand);

        std::cout << "Модель: ";
        std::getline(std::cin, model);
        
        std::cout << "Год выпуска: ";
        year = getIntegerInput();

        std::cout << "Пробег: ";
        mileage = getIntegerInput();

        cars[i].setBrand(brand);
        cars[i].setModel(model);
        cars[i].setYear(year);
        cars[i].setMileage(mileage);
    }

    // Запрашиваем год для фильтрации
    std::cout << "\nВведите год, после которого выпущены автомобили для вывода: ";
    int filterYear = getIntegerInput();

    // Выводим все автомобили, выпущенные после определённого года
    std::cout << "\nАвтомобили, выпущенные после " << filterYear << " года" << std::endl;
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (cars[i].getYear() > filterYear) {
            cars[i].print();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Таких автомобилей не найдено." << std::endl;
    }

    // 4. Освобождаем выделенную память
    delete[] cars;
    cars = nullptr;

    return 0;
}