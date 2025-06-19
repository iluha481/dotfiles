#include <iostream>
#include <string>

// Класс для представления контактной записи
class Contact {
private:
    std::string name;
    std::string phoneNumber;
    std::string address;

public:
    // Конструктор с параметрами для инициализации полей
    Contact(std::string n = "", std::string p = "", std::string a = "")
        : name(n), phoneNumber(p), address(a) {}

    // Геттеры 
    std::string getName() const {
        return name;
    }

    std::string getPhoneNumber() const {
        return phoneNumber;
    }

    std::string getAddress() const {
        return address;
    }

    // Сеттеры 
    void setName(const std::string& n) {
        name = n;
    }

    void setPhoneNumber(const std::string& p) {
        phoneNumber = p;
    }

    void setAddress(const std::string& a) {
        address = a;
    }

    // Метод для вывода информации о контакте
    void print() const {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Номер телефона: " << phoneNumber << std::endl;
        std::cout << "Адрес: " << address << std::endl;
    }
};



int main() {
    // Отображение русских символов в консоли
    setlocale(LC_ALL, "Russian");

    int n;
    std::cout << "Введите количество контактов (N): ";
    std::cin >> n;
    // Проверка на корректный ввод числа
    while (n <= 0) {
        std::cin.ignore();
        std::cout << "Ошибка. Введите положительное число: ";
        std::cin.clear();
        std::cin >> n;
        
    }
    // Очищает буфер ввода
    // если не сделать, то один getline не сработает
    std::cin.ignore();
    // Динамически выделяем массив из N объектов класса Contact
    Contact* contacts = new Contact[n];

    // Заполняем его данными от пользователя
    // getline нужен чтобы ввести строку с пробелами
    for (int i = 0; i < n; ++i) {
        std::string name, phone, address;
        std::cout << "\nВведите данные для контакта #" << i + 1 << ":" << std::endl;

        std::cout << "Имя: ";
        std::getline(std::cin, name);

        std::cout << "Номер телефона (оставьте пустым, если нет): ";
        std::getline(std::cin, phone);

        std::cout << "Адрес: ";
        std::getline(std::cin, address);

        contacts[i].setName(name);
        contacts[i].setPhoneNumber(phone);
        contacts[i].setAddress(address);
    }

    // Выводим все контакты, у которых есть номер телефона
    std::cout << "\nКонтакты с указанным номером телефона" << std::endl;
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (!contacts[i].getPhoneNumber().empty()) {
            contacts[i].print();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Контактов с номерами телефонов не найдено." << std::endl;
    }

    // Освобождаем выделенную память в конце программы
    delete[] contacts;

    return 0;
}