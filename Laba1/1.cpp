#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер массива: ";
	cin >> n;
	while (n <= 0) {
		cout << "Введенно некорректное число! Повторите попытку: ";
		cin >> n;
	}

	//Выделаем динамическую память для массива
	int* arr = new int[n];
	cout << "Пожалуйста, заполните массив: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	cout << endl;
	cout << "Содержимое массива: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i];
	}
	cout << endl;
	cout << "Адрес начала массива: " << & arr[0] << endl;

	delete[] arr;
	return 0;

}