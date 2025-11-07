#include <iostream>
using namespace std;

int main() {
	const int n = 10;

	//Выделаем динамическую память для массива
	short* arr = new short[n];
	cout << "Пожалуйста, заполните массив: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	cout << endl;
	cout << "Содержимое массива: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
	cout << "Адрес начала массива: " << &arr[0] << endl;

	delete[] arr;
	return 0;

}