#include <iostream>
#include <string>
#include <vector>

// Структура Date
struct Date {
    int day;
    int month;
    int year;

    void print() const {
        std::cout << day << "." << month << "." << year;
    }
};

// Класс Book
class Book {
private:
    std::string author;
    std::string title;
    int isbn;
    Date publicationDate;
    int quantity;

public:
    // Конструктор с параметрами
    Book(std::string a = "", std::string t = "", int i = 0, Date d = {1, 1, 2000}, int q = 0)
        : author(a), title(t), isbn(i), publicationDate(d), quantity(q) {}

    // Геттеры и сеттеры
    // const означает, что данные объекта не будут изменены
    void setAuthor(const std::string& a) { author = a; }
    std::string getAuthor() const { return author; }

    void setTitle(const std::string& t) { title = t; }
    std::string getTitle() const { return title; }

    void setIsbn(int i) { isbn = i; }
    int getIsbn() const { return isbn; }

    void setPublicationDate(const Date& d) { publicationDate = d; }
    Date getPublicationDate() const { return publicationDate; }

    void setQuantity(int q) { quantity = q; }
    int getQuantity() const { return quantity; }


    // Метод вывода информации о книге
    void print() const {
        std::cout << "Название: " << title << std::endl;
        std::cout << "Автор: " << author << std::endl;
        std::cout << "ISBN: " << isbn << std::endl;
        std::cout << "Дата издания: ";
        publicationDate.print();
        std::cout << "\nКоличество экземпляров: " << quantity << std::endl;
    }
};

// Класс Library
class Library {
private:
    Book* books; // Динамический массив книг
    int bookCount; // Текущее количество книг
    int capacity; // Вместимость массива 

    // Приватный метод для расширения массива
    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2; // Увеличиваем вместимость
        // Копируем старый массив в новый
        Book* newBooks = new Book[capacity];
        for (int i = 0; i < bookCount; ++i) {
            newBooks[i] = books[i];
        }
        delete[] books;
        books = newBooks;
    }

public:
    // Конструктор
    Library() : books(nullptr), bookCount(0), capacity(0) {}

    // Деструктор для освобождения памяти
    ~Library() {
        delete[] books;
    }

    // Метод добавления книги
    void addBook(const Book& book) {
        if (bookCount == capacity) {
            resize();
        }
        books[bookCount++] = book;
        std::cout << "Книга \"" << book.getTitle() << "\" успешно добавлена." << std::endl;
    }

    // Метод удаления книги по ISBN
    void removeBookByIsbn(int isbn) {
        // Проверяем, есть ли эта книга в библиотеке
        int foundIndex = -1;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getIsbn() == isbn) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            // Сдвигаем элементы
            for (int i = foundIndex; i < bookCount - 1; ++i) {
                books[i] = books[i + 1];
            }
            bookCount--;
            std::cout << "Книга с ISBN " << isbn << " удалена." << std::endl;
        } else {
            std::cout << "Книга с ISBN " << isbn << " не найдена." << std::endl;
        }
    }

    // Метод поиска по автору или названию
    void findBook(const std::string& query) const {
        std::cout << "\nРезультаты поиска по запросу \"" << query << "\"\n";
        bool found = false;
        for (int i = 0; i < bookCount; ++i) {
            // Ищем совпадение, даже частичное
            // npos - код ошибки, если ничего не найдено
            if (books[i].getAuthor().find(query) != std::string::npos ||
                books[i].getTitle().find(query) != std::string::npos) {
                books[i].print();
                found = true;
            }
        }
        if (!found) {
            std::cout << "Книги не найдены.\n";
        }
    }

    // Метод вывода всех книг
    void printAllBooks() const {
        std::cout << "\nВсе книги в библиотеке\n";
        if (bookCount == 0) {
            std::cout << "Библиотека пуста.\n";
            return;
        }
        for (int i = 0; i < bookCount; ++i) {
            books[i].print();
        }
    }

    // Метод фильтрации по году издания
    void filterByYear(int year) const {
        std::cout << "\nКниги, изданные в " << year << " году\n";
        bool found = false;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getPublicationDate().year == year) {
                books[i].print();
                found = true;
            }
        }
        if (!found) {
            std::cout << "Книги за этот год не найдены.\n";
        }
    }
};

/*
Наследование не нашёл где использовать
Можно сделать разные типы книг по жанрам или чето такое
*/

int main() {
    setlocale(LC_ALL, "Russian");

    Library myLibrary;

    // Добавляем книги
    myLibrary.addBook(Book("Джордж Оруэлл", "1984", 12345, {1, 1, 1949}, 5));
    myLibrary.addBook(Book("Рэй Брэдбери", "451 градус по Фаренгейту", 11223, {1, 1, 1953}, 7));
    myLibrary.addBook(Book("Джордж Оруэлл", "Скотный двор", 54321, {1, 1, 1949}, 4));

    // Выводим все книги
    myLibrary.printAllBooks();

    // Ищем книги
    myLibrary.findBook("Оруэлл");

    // Фильтруем по году
    myLibrary.filterByYear(1949);

    // Удаляем книгу
    myLibrary.removeBookByIsbn(67890);

    // Выводим все книги
    myLibrary.printAllBooks();

    return 0;
}