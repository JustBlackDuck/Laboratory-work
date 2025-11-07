#include <iostream>
#include <string>
using namespace std;

// Класс для хранения данных о продажах
class Sales {
protected:
   float sales[3]; // Массив для хранения продаж за последние 3 месяца
public:
   void getdata() {
       cout << "Введите продажи за последние 3 месяца:" << endl;
       for (int i = 0; i < 3; i++) {
           cout << "Месяц " << (i + 1) << ": ";
           cin >> sales[i];
       }
       cin.ignore(); // Очистка буфера после ввода чисел
   }

   void putdata() {
       cout << "Продажи за последние 3 месяца:" << endl;
       for (int i = 0; i < 3; i++) {
           cout << "Месяц " << (i + 1) << ": " << sales[i] << " руб." << endl;
       }
   }
};

// Базовый класс Publication
class Publication {
protected:
   string title;
   float price;
public:
   void getdata() {
       cout << "Введите название: ";
       getline(cin, title);
       cout << "Введите цену: ";
       cin >> price;
       cin.ignore();
   }

   void putdata() {
       cout << "Название: " << title << endl;
       cout << "Цена: " << price << " руб." << endl;
   }
};

// Класс Book, наследуется от Publication и Sales
class Book : public Publication, public Sales {
private:
   int pages;
public:
   void getdata() {
       Publication::getdata();
       cout << "Введите количество страниц: ";
       cin >> pages;
       cin.ignore();
       Sales::getdata();
   }

   void putdata() {
       Publication::putdata();
       cout << "Количество страниц: " << pages << endl;
       Sales::putdata();
   }
};

// Класс Type, наследуется от Publication и Sales
class Type : public Publication, public Sales {
private:
   float minutes;
public:
   void getdata() {
       Publication::getdata();
       cout << "Введите длительность записи: ";
       cin >> minutes;
       cin.ignore();
       Sales::getdata();
   }

   void putdata() {
       Publication::putdata();
       cout << "Длительность записи: " << minutes << " минут" << endl;
       Sales::putdata();
   }
};

int main() {

   Book book;
   Type type;

   cout << "ВВОД ДАННЫХ" << endl;
   cout << "\nКнига" << endl;
   book.getdata();

   cout << "\nАудиокнига" << endl;
   type.getdata();

   cout << "\nРЕЗУЛЬТАТЫ" << endl;
   cout << "\nКнига" << endl;
   book.putdata();

   cout << "\nАудиокнига" << endl;
   type.putdata();

   cout << "\nПрограмма завершена. Нажмите Enter для выхода...";
   cin.get();

   return 0;
}