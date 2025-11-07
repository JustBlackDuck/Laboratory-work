#include <iostream>
#include <string>
using namespace std;

// Базовый класс всех ошибок
class ProgramError : public exception {
   string msg;
public:
   ProgramError(const string& m) : msg(m) {}
   const char* what() const noexcept override { return msg.c_str(); }
};

// "Ошибочный указатель"
class InvalidPointerError : public ProgramError {
public:
   InvalidPointerError() : ProgramError("Ошибочный указатель") {}
};

//Общая "ошибка работы со списком" (база для двух других)
class ListError : public ProgramError {
public:
   ListError(const string& m) : ProgramError("Ошибка работы со списком: " + m) {}
};

// "Недопустимый индекс"
class InvalidIndexError : public ListError {
public:
   InvalidIndexError(size_t i, size_t s)
       : ListError("недопустимый индекс") {
   }
};

//"Список переполнен"
class ListOverflowError : public ListError {
public:
   ListOverflowError() : ListError("список переполнен") {}
};

// Шаблонный класс для хранения массива УКАЗАТЕЛЕЙ на объекты типа T
template <typename T>
class PointerArray {
   T** arr;        // массив указателей на T
   size_t len;     // текущее количество элементов
   size_t cap;     // максимальная вместимость

public:
   // Конструктор: выделяет память под cap указателей
   explicit PointerArray(size_t cap = 10) : cap(cap), len(0) {
       arr = new T * [cap];
   }

   // Деструктор: удаляет все объекты и сам массив указателей
   ~PointerArray() {
       for (size_t i = 0; i < len; ++i)
           delete arr[i];   // освобождаем каждый объект
       delete[] arr;        // освобождаем массив указателей
   }

   // Добавление указателя в массив
   void push_back(T* p) {
       if (p == nullptr)
           throw InvalidPointerError();     // проверка указателя
       if (len >= cap)
           throw ListOverflowError();       // проверка переполнения
       arr[len++] = p;
   }

   // Перегрузка оператора [] — для изменения элемента
   T*& operator[](size_t i) {
       if (i >= len)
           throw InvalidIndexError(i, len); // проверка индекса
       return arr[i];
   }

   // Перегрузка оператора [] — для чтения (const-версия)
   const T* operator[](size_t i) const {
       if (i >= len)
           throw InvalidIndexError(i, len);
       return arr[i];
   }
};

// Примеры классов для демонстрации (любые два разных)
class A {
public:
   A() { cout << "Создан объект A\n"; }
   ~A() { cout << "Удалён объект A\n"; }
   void say() const { cout << "Это A\n"; }
};

class B {
public:
   int x;
   B(int v) : x(v) { cout << "Создан объект B с x=" << x << "\n"; }
   ~B() { cout << "Удалён объект B с x=" << x << "\n"; }
   void print() const { cout << "B.x = " << x << "\n"; }
};

// Основная функция — демонстрация
int main() {
   // Работа с классом A
   try {
       PointerArray<A> listA(2);
       listA.push_back(new A());
       listA.push_back(new A());
       // listA.push_back(new A()); // ← вызовет "список переполнен"

       listA[0]->say();
       // listA[5]->say(); // ← вызовет "недопустимый индекс"
   }
   catch (const ProgramError& e) {
       cout << "Исключение: " << e.what() << endl;
   }

   // Работа с классом B
   try {
       PointerArray<B> listB(2);
       listB.push_back(new B(10));
       listB.push_back(new B(20));

       listB[0]->print();
       listB[1]->print();
   }
   catch (const ProgramError& e) {
       cout << "Исключение: " << e.what() << endl;
   }

   // Память автоматически освобождается деструкторами
   return 0;
}