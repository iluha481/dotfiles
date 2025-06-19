#include <iostream>
#include <string>

// Базовый класс для динамического массива строк
class StringArray {
protected: // protected, чтобы производные классы имели доступ
    std::string* data; // указатель на массив строк
    int size;

public:
    // Конструктор, выделяет память под массив
    StringArray(int initialSize = 0) : size(initialSize) {
        if (size > 0) {
            data = new std::string[size];
        } else {
            data = nullptr;
        }
    }

    // Деструктор, освобождает выделенную память
    virtual ~StringArray() {
        delete[] data;
    }

    // Метод добавления строки в конец массива
    virtual void add(const std::string& str) {
        // Создаем новый массив на 1 элемент больше
        std::string* newData = new std::string[size + 1];
        // Копируем старые данные
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        // Добавляем новый элемент
        newData[size] = str;
        // Удаляем старый массив
        delete[] data;
        // Меняем указатель на новый массив
        data = newData;
        size++;
    }

    // Метод удаления строки по индексу
    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Ошибка: неверный индекс." << std::endl;
            return;
        }
        // Создаем новый массив на 1 элемент меньше
        std::string* newData = new std::string[size - 1];
        int newIndex = 0;
        // Копируем данные, пропуская удаляемый элемент
        for (int i = 0; i < size; ++i) {
            if (i != index) {
                newData[newIndex] = data[i];
                newIndex++;
            }
        }
        // Удаляем старый массив
        delete[] data;
        data = newData;
        size--;
    }

    // Метод для вывода массива на экран
    void print() const {
        if (size == 0) {
            std::cout << "Массив пуст." << std::endl;
            return;
        }
        std::cout << "Содержимое массива:" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << "[" << i << "]: " << data[i] << std::endl;
        }
    }

    // Геттер для размера
    int getSize() const {
        return size;
    }
};

// Производный класс, который не позволяет добавлять дублирующиеся строки
class UniqueStringArray : public StringArray {
public:
    // Используем конструктор базового класса
    UniqueStringArray(int initialSize = 0) : StringArray(initialSize) {}

    // Переопределенный метод добавления
    void add(const std::string& str) override {
        // Проверяем, есть ли такая строка в массиве
        for (int i = 0; i < size; ++i) {
            if (data[i] == str) {
                std::cout << "Строка \"" << str << "\" уже существует." << std::endl;
                return; // Если нашли дубликат, выходим из метода
            }
        }
        // Если дубликата нет, вызываем метод add базового класса
        StringArray::add(str);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "UniqueStringArray" << std::endl;
    UniqueStringArray uniqueArr;
    uniqueArr.add("hello");
    uniqueArr.add("world");
    uniqueArr.add("hello"); // Добавляем дубликат
    uniqueArr.add("c++");
    uniqueArr.print();

    std::cout << "\nУдаляем элемент с индексом 1" << std::endl;
    uniqueArr.remove(1);
    uniqueArr.print();

    // Очищать память не обязательно, 
    // деструктор вызовется автоматически при выходе из области видимости
    return 0;
}