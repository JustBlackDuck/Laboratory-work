#include <iostream>
#include <string>
using namespace std;

// Базовый класс для данных о продажах
class Sales {
protected:
   float sales[3];  // массив для продаж за 3 месяца

public:
   // Конструктор - обнуляем массив
   Sales() {
       for (int i = 0; i < 3; i++) {
           sales[i] = 0.0f;
       }
   }

   // Метод для ввода данных о продажах
   void getSalesData() {
       cout << "Введите продажи за последние 3 месяца:" << endl;
       for (int i = 0; i < 3; i++) {
           cout << "Месяц " << (i + 1) << ": ";
           cin >> sales[i];
       }
   }

   // Метод для вывода данных о продажах
   void putSalesData() {
       cout << "Продажи за 3 месяца: ";
       for (int i = 0; i < 3; i++) {
           cout << sales[i];
           if (i < 2) cout << ", ";
       }
       cout << " руб." << endl;
   }
};

// Базовый класс Publication (Публикация)
class Publication {
protected:
   string title;    // название книги
   float price;     // цена

public:
   // Конструктор по умолчанию
   Publication() : title(""), price(0.0f) {}

   // Виртуальный метод для ввода данных
   virtual void getdata() {
       cout << "Введите название: ";
       cin.ignore(); // очищаем буфер перед вводом строки
       getline(cin, title);
       cout << "Введите цену: ";
       cin >> price;
   }

   // Виртуальный метод для вывода данных
   virtual void putdata() {
       cout << "Название: " << title << endl;
       cout << "Цена: " << price << " руб." << endl;
   }

   // Виртуальный деструктор
   virtual ~Publication() {}
};

// Класс Book наследуется от Publication и Sales
class Book : public Publication, public Sales {
private:
   int pages;  // количество страниц

public:
   // Конструктор
   Book() : pages(0) {}

   // Переопределяем метод ввода данных
   void getdata() override {
       Publication::getdata(); // вводим основные данные
       cout << "Введите количество страниц: ";
       cin >> pages;
       Sales::getSalesData(); // вводим данные о продажах
   }

   // Переопределяем метод вывода данных
   void putdata() override {
       Publication::putdata(); // выводим основные данные
       cout << "Количество страниц: " << pages << endl;
       Sales::putSalesData(); // выводим данные о продажах
       cout << "------------------------" << endl;
   }
};

// Класс Type наследуется от Publication и Sales
class Type : public Publication, public Sales {
private:
   float minutes;  // время записи в минутах

public:
   // Конструктор
   Type() : minutes(0.0f) {}

   // Переопределяем метод ввода данных
   void getdata() override {
       Publication::getdata(); // вводим основные данные
       cout << "Введите время записи (минуты): ";
       cin >> minutes;
       Sales::getSalesData(); // вводим данные о продажах
   }

   // Переопределяем метод вывода данных
   void putdata() override {
       Publication::putdata(); // выводим основные данные
       cout << "Время записи: " << minutes << " минут" << endl;
       Sales::putSalesData(); // выводим данные о продажах
       cout << "------------------------" << endl;
   }
};

// Главная функция для тестирования
int main() {

   // Создаем объекты
   Book book1;
   Type type1;

   cout << "=== Ввод данных для книги ===" << endl;
   book1.getdata();

   cout << "\n=== Ввод данных для аудиозаписи ===" << endl;
   type1.getdata();

   cout << "\n=== Вывод всех данных ===" << endl;
   cout << "Книга:" << endl;
   book1.putdata();

   cout << "Аудиозапись:" << endl;
   type1.putdata();

   return 0;
}