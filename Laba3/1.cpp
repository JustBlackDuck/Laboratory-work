#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Предварительное объявление классов
class Component;
class Assembly;

// Объявления шаблонной функции
template<typename T, typename... Args>
shared_ptr<T> createComponent(Args&&... args);

// Базовый класс Component (Деталь)
class Component {
protected:
   string name;
   double weight;

   // Защищенный конструктор
   Component(const string& n, double w) : name(n), weight(w) {}

public:
   virtual ~Component() = default;

   // Виртуальные методы
   virtual void display() const {
       cout << "Деталь: " << name << ", Вес: " << weight << " кг" << endl;
   }

   virtual double getTotalWeight() const {
       return weight;
   }

   // Объявляем дружественной всю шаблонную функцию
   template<typename U, typename... Args>
   friend shared_ptr<U> createComponent(Args&&... args);

   // Геттеры
   string getName() const { return name; }
   double getWeight() const { return weight; }
};

// Производный класс Assembly (Сборка)
class Assembly : public Component {
protected:
   vector<shared_ptr<Component>> components;

   // Защищенный конструктор
   Assembly(const string& n, double w) : Component(n, w) {}

public:
   // Метод для добавления компонентов
   void addComponent(shared_ptr<Component> component) {
       components.push_back(component);
   }

   // Переопределенные виртуальные методы
   void display() const override {
       cout << "Сборка: " << name << ", Базовый вес: " << weight
           << " кг, Компонентов: " << components.size()
           << ", Общий вес: " << getTotalWeight() << " кг" << endl;

       // Отображение всех компонентов
       for (const auto& comp : components) {
           cout << "  - ";
           comp->display();
       }
   }

   double getTotalWeight() const override {
       double total = weight; // Базовый вес сборки
       for (const auto& comp : components) {
           total += comp->getTotalWeight();
       }
       return total;
   }

   // Объявляем дружественной всю шаблонную функцию
   template<typename U, typename... Args>
   friend shared_ptr<U> createComponent(Args&&... args);
};

// Реализация шаблонной функции
template<typename T, typename... Args>
shared_ptr<T> createComponent(Args&&... args) {
   return shared_ptr<T>(new T(forward<Args>(args)...));
}

int main() {
   setlocale(LC_ALL, "Russian");
   // Вектор для хранения компонентов
   vector<shared_ptr<Component>> storage;

   // Создание деталей с помощью дружественной функции
   auto bolt = createComponent<Component>("Болт M10", 0.1);
   auto nut = createComponent<Component>("Гайка M10", 0.05);
   auto washer = createComponent<Component>("Шайба 10mm", 0.02);
   auto bearing = createComponent<Component>("Подшипник 6000", 0.3);
   auto shaft = createComponent<Component>("Вал d20mm", 1.5);

   // Создание сборок
   auto fasteningKit = createComponent<Assembly>("Комплект крепежа", 0.01);
   auto mechanism = createComponent<Assembly>("Механизм привода", 2.0);

   // Добавление компонентов в сборки
   fasteningKit->addComponent(bolt);
   fasteningKit->addComponent(nut);
   fasteningKit->addComponent(washer);

   mechanism->addComponent(shaft);
   mechanism->addComponent(bearing);
   mechanism->addComponent(fasteningKit); // Вложенная сборка!

   // Добавление всех объектов в хранилище
   storage.push_back(bolt);
   storage.push_back(nut);
   storage.push_back(washer);
   storage.push_back(bearing);
   storage.push_back(shaft);
   storage.push_back(fasteningKit);
   storage.push_back(mechanism);

   // Вывод информации о всех компонентах
   cout << "=== Все компоненты в хранилище ===" << endl;
   for (const auto& component : storage) {
       component->display();
       cout << endl;
   }

   // Демонстрация полиморфизма
   cout << "=== Демонстрация полиморфизма ===" << endl;
   Component* polyComponent = mechanism.get();
   polyComponent->display();

   // Вывод общего веса механизма
   cout << "\nОбщий вес механизма: " << mechanism->getTotalWeight() << " кг" << endl;

   return 0;
}