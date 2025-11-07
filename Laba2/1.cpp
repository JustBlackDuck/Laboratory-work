#include <iostream>
#include <string>
using namespace std;

class Publication {
protected:
   string title;
   float price;
public:
   void getdata() {
       cout << "Введите название: ";
       getline(cin, title);  // getline для ввода строки с пробелами
       cout << "Введите цену: ";
       cin >> price;
       cin.ignore();  // Очистка буфера после ввода числа
   }

   void putdata() {
       cout << "Название: " << title << endl;
       cout << "Цена: " << price << " руб." << endl;
   }
};

class Book : public Publication {  // Наследование от класса Publication
private:
   int pages;
public:
   void getdata() {
       Publication::getdata();  // Вызов метода базового класса
       cout << "Введите количество страниц: ";
       cin >> pages;
       cin.ignore();  // Очистка буфера после ввода числа
   }

   void putdata() {
       Publication::putdata();  // Вызов метода базового класса
       cout << "Количество страниц: " << pages << endl;
   }
};

class Type : public Publication {  // Наследование от класса Publication
private:
   float minutes;
public:
   void getdata() {
       Publication::getdata();  // Вызов метода базового класса
       cout << "Введите длительность записи: ";
       cin >> minutes;
       cin.ignore();  // Очистка буфера после ввода числа
   }

   void putdata() {
       Publication::putdata();  // Вызов метода базового класса
       cout << "Длительность записи: " << minutes << " минут" << endl;
   }
};

int main() {
   Book book;   // Создание объекта класса Book
   Type type;   // Создание объекта класса Type

   cout << "ВВОД ДАННЫХ" << endl;
   cout << "\nКнига" << endl;
   book.getdata();  // Вызов метода ввода данных для книги

   cout << "\nАудиокнига" << endl;
   type.getdata();  // Вызов метода ввода данных для аудиокниги

   cout << "\nРЕЗУЛЬТАТЫ" << endl;
   cout << "\nКнига" << endl;
   book.putdata();  // Вызов метода вывода данных для книги

   cout << "\nАудиокнига" << endl;
   type.putdata();  // Вызов метода вывода данных для аудиокниги

   // Пауза чтобы консоль не закрывалась
   cout << "\nПрограмма завершена. Нажмите Enter для выхода...";
   cin.get();  // Ожидание нажатия Enter (пауза перед закрытием консоли)

   return 0;
}