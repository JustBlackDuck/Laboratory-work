#include <iostream>
#include <vector>
#include <memory>
#include <random>
using namespace std;

// Базовый класс
class Base {
public:
   virtual ~Base() = default;
   virtual void showType() const {
       cout << "Базовый класс" << endl;
   }
   virtual int calculate() const {
       return 1;
   }
};

// Производный класс
class Derived : public Base {
public:
   void showType() const override {
       cout << "Производный класс" << endl;
   }
   int calculate() const override {
       return 2;
   }
};

// Функция для добавления объектов в хранилище
void add(vector<unique_ptr<Base>>& storage, unique_ptr<Base> obj) {
   storage.push_back(move(obj));
}

int main() {
   vector<unique_ptr<Base>> storage;

   // Инициализация генератора случайных чисел
   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<> dis(1, 10);

   cout << "=== Создание объектов ===" << endl;

   // Создание объектов в цикле
   for (int i = 0; i < 5; ++i) {
       int randomValue = dis(gen);

       if (randomValue % 2 == 0) {
           // Четное число - создаем Base
           cout << "Создан Base (случайное значение: " << randomValue << ")" << endl;
           auto obj = make_unique<Base>();
           add(storage, move(obj));
       }
       else {
           // Нечетное число - создаем Derived
           cout << "Создан Derived (случайное значение: " << randomValue << ")" << endl;
           auto obj = make_unique<Derived>();
           add(storage, move(obj));
       }
   }

   cout << "\n=== Демонстрация полиморфного поведения ===" << endl;

   // Демонстрация полиморфного поведения
   for (size_t i = 0; i < storage.size(); ++i) {
       cout << "Объект " << i + 1 << ": ";
       storage[i]->showType();
       cout << "Результат вычисления: " << storage[i]->calculate() << endl;
       cout << "---" << endl;
   }

   cout << "=== Освобождение ресурсов ===" << endl;

   // Автоматическое освобождение ресурсов (благодаря unique_ptr)
   storage.clear();
   cout << "Все ресурсы освобождены." << endl;

   return 0;
}