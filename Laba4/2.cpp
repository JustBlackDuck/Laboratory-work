#include <iostream>
#include <string>
#include <stdexcept> // для использования range_error
using namespace std;

// Базовый класс всех ошибок программы
class ProgramError : public exception {
    string msg;
public:
    ProgramError(const string& m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Ошибочный указатель
class InvalidPointerError : public ProgramError {
public:
    InvalidPointerError() : ProgramError("Ошибочный указатель") {}
};

// Общая ошибка работы со списком
class ListError : public ProgramError {
public:
    ListError(const string& m) : ProgramError("Ошибка работы со списком: " + m) {}
};

// Недопустимый индекс
class InvalidIndexError : public ListError {
public:
    InvalidIndexError(size_t i, size_t s) : ListError("недопустимый индекс") {}
};

// Список переполнен
class ListOverflowError : public ListError {
public:
    ListOverflowError() : ListError("список переполнен") {}
};

// Шаблонный класс для хранения массива УКАЗАТЕЛЕЙ на объекты произвольного типа
template <typename T>
class PointerArray {
    T** arr;        // массив указателей на T
    size_t len;     // текущее количество элементов
    size_t cap;     // максимальная ёмкость

public:
    explicit PointerArray(size_t capacity = 10) : cap(capacity), len(0) {
        arr = new T * [cap];
    }

    ~PointerArray() {
        for (size_t i = 0; i < len; ++i)
            delete arr[i];   // удаляем каждый объект
        delete[] arr;        // удаляем массив указателей
    }

    // Добавление указателя
    void push_back(T* ptr) {
        if (ptr == nullptr)
            throw InvalidPointerError();
        if (len >= cap)
            throw ListOverflowError();
        arr[len++] = ptr;
    }

    // Оператор [] — выбрасывает собственное исключение
    T*& operator[](size_t index) {
        if (index >= len)
            throw InvalidIndexError(index, len);
        return arr[index];
    }

    const T* operator[](size_t index) const {
        if (index >= len)
            throw InvalidIndexError(index, len);
        return arr[index];
    }

    // Метод at() — выбрасывает СТАНДАРТНОЕ исключение range_error при выходе за границы
    T* at(size_t index) {
        if (index >= len) {
            throw range_error("Индекс выходит за пределы допустимого диапазона");
        }
        return arr[index];
    }
};

// Пример класса 1
class Device {
public:
    Device() { cout << "Создан Device\n"; }
    ~Device() { cout << "Удалён Device\n"; }
    void info() const { cout << "Это устройство\n"; }
};

// Пример класса 2
class Sensor {
public:
    double value;
    Sensor(double v) : value(v) { cout << "Создан Sensor (значение: " << value << ")\n"; }
    ~Sensor() { cout << "Удалён Sensor (значение: " << value << ")\n"; }
    void read() const { cout << "Показания датчика: " << value << "\n"; }
};

// Основная функция
int main() {
    // Часть 1: работа с собственными исключениями
    try {
        PointerArray<Device> devices(2);
        devices.push_back(new Device());
        devices.push_back(new Device());

        devices[0]->info();
        // devices[5]->info(); // вызвало бы InvalidIndexError
    }
    catch (const ProgramError& e) {
        cout << "Обработка собственного исключения: " << e.what() << "\n";
    }

    // Часть 2: работа с range_error (требуется по заданию)
    try {
        PointerArray<Sensor> sensors(2);
        sensors.push_back(new Sensor(23.5));
        sensors.push_back(new Sensor(41.0));

        // Корректный доступ через at()
        sensors.at(0)->read();

        // Некорректный доступ — вызовет std::range_error
        cout << "Попытка доступа к несуществующему элементу...\n";
        sensors.at(10)->read(); // ← выбросит range_error
    }
    catch (const range_error& e) {
        // === ОБРАБОТКА ТРЕБУЕМОГО ИСКЛЮЧЕНИЯ ===
        cout << "Перехвачено и обработано исключение range_error: " << e.what() << "\n";
    }
    catch (const ProgramError& e) {
        cout << "Собственное исключение: " << e.what() << "\n";
    }

    cout << "\nПрограмма завершена. Вся память освобождена.\n";
    return 0;
}