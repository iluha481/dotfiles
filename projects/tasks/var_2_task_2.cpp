#include <iostream>

// Базовый класс для динамического массива целых чисел
class IntArray {
protected:
    int* data;
    int size;

public:
    // Конструктор
    IntArray(int initialSize = 0) : size(initialSize) {
        if (size > 0) {
            data = new int[size];
        } else {
            data = nullptr;
        }
    }

    // Деструктор
    virtual ~IntArray() {
        delete[] data;
    }

    // Метод добавления элемента в конец
    virtual void add(int value) {
        // Создаем новый массив большего размера
        int* newData = new int[size + 1];
        // Копируем старые элементы
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        // Добавляем новый элемент
        newData[size] = value;
        // Удаляем старый массив
        delete[] data;
        // Обновляем указатель и размер
        data = newData;
        size++;
    }

    // Метод удаления элемента по индексу
    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Ошибка: неверный индекс для удаления." << std::endl;
            return;
        }
        // Создаем новый массив меньшего размера
        int* newData = new int[size - 1];
        int newIndex = 0;
        // Копируем элементы, пропуская удаляемый
        for (int i = 0; i < size; ++i) {
            if (i != index) {
                newData[newIndex++] = data[i];
            }
        }
        delete[] data;
        data = newData;
        size--;
    }

    // Метод вывода массива
    void print() const {
        if (size == 0) {
            std::cout << "Массив пуст." << std::endl;
            return;
        }
        std::cout << "Массив: [ ";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    // Геттер размера
    int getSize() const {
        return size;
    }
};

// Производный класс для уникальных значений
class UniqueArray : public IntArray {
public:
    // Используем конструктор базового класса
    UniqueArray(int initialSize = 0) : IntArray(initialSize) {}

    // Переопределенный метод добавления
    void add(int value) override {
        // Сначала проверяем, есть ли уже такое значение
        for (int i = 0; i < size; ++i) {
            if (data[i] == value) {
                std::cout << "Значение " << value << " уже есть в массиве. Добавление отменено." << std::endl;
                return; // Выходим, если нашли дубликат
            }
        }
        // Если дубликата нет, вызываем родительский метод add
        IntArray::add(value);
        std::cout << "Значение " << value << " добавлено." << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "UniqueArray" << std::endl;
    UniqueArray arr;
    arr.print();
    
    arr.add(10);
    arr.add(20);
    arr.add(10); // Добавляем дубликат
    arr.add(30);
    arr.print();

    std::cout << "\nУдаляем элемент с индексом 1" << std::endl;
    arr.remove(1);
    arr.print();

    return 0;
}