#include <iostream>
#include <clocale>
#include <string>
#include <ctime>

#include "BDinamicArray.h"
#include "BList.h"
#include "BStack.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	BootstrappedDinamicArray<int> arr1;
	BootstrappedDinamicArray<int> arr2;
	BootstrappedDinamicArray<int> arr3;
	BootstrappedDinamicArray<int> arr4;

	BootstrappedList<int> list1;
	BootstrappedList<int> list2;
	BootstrappedList<int> list3;

	BootstrappedStack<int> bs, sb;

	std::setlocale(LC_ALL, "Russian");
	
	cout << "Bootstrapping. Структуры данных." << endl;
	cout << "Динамический массив." << endl;
	
	cout << "Добавим 10 элементов в arr1, arr2, arr3:" << endl;

	for (int i = 0; i < 10; i++)
	{
		arr1.push(i);
		arr2.push(10 + i);
		arr3.push(20 + i);
	}
	
	cout << "Длина arr1 =  " << arr1.length() << endl;
	cout << "arr1: " << endl;
	for (int i = 0; i < arr1.length(); i++)
		cout << arr1[i] << ' ';
	cout << endl;

	cout << "arr2: " << endl;
	for (int i = 0; i < arr2.length(); i++)
		cout << arr2[i] << ' ';
	cout << endl;

	cout << "arr3: " << endl;
	for (int i = 0; i < arr3.length(); i++)
		cout << arr3[i] << ' ';
	cout << endl;

	cout << "Присоединим к arr2 arr3 arr4, а к arr1 arr2:" << endl;
	arr4.push(100);
	arr4.push(200);

	arr2.join(arr3);
	arr2.join(arr4);
	arr1.join(arr2);

	arr1.push(123);

	cout << "Длина arr2 = " << arr2.length() << endl;
	for (int i = 0; i < arr2.length(); i++)
		cout << arr2[i] << ' ';
	cout << endl;
	
	cout << "Длина arr1 = " << arr1.length() << endl;

	for (int i = 0; i < arr1.length(); i++)
	{
		cout << arr1[i] << ' ';
	}
	cout << endl;

	cout << "Список." << endl;

	list1.push(10);
	list1.push(20);
	list1.push(30);
	list1.push(40);

	cout << "Длина списка list1 = " << list1.length() << endl;
	for (size_t i = 0; i < list1.length(); i++)
		cout << list1.GetItemByIndex(i)->GetValue() << ' ';
	cout << endl;

	list2.push(50);
	list2.push(60);

	cout << "Длина списка list2 = " << list2.length() << endl;
	for (size_t i = 0; i < list2.length(); i++)
		cout << list2.GetItemByIndex(i)->GetValue() << ' ';
	cout << endl;

	list3.push(70);
	list3.push(80);
	list3.push(90);

	cout << "Длина списка list3 = " << list3.length() << endl;
	for (size_t i = 0; i < list3.length(); i++)
		cout << list3.GetItemByIndex(i)->GetValue() << ' ';
	cout << endl;

	cout << "Присоединим к list2 list3, а к list1 list2:" << endl;
	list2.join(list3);
	cout << "List2:" << endl;
	for (size_t i = 0; i < list2.length(); i++)
		cout << list2.GetItemByIndex(i)->GetValue() << ' ';
	cout << endl;

	list1.join(list2);
	cout << "List1:" << endl;
	for (size_t i = 0; i < list1.length(); i++)
		cout << list1.GetItemByIndex(i)->GetValue() << ' ';
	cout << endl;
	
	cout << "Добавим к списку list1 число 777." << endl;
	list1.push(777);
	cout << "Длина списка list2 = " << list2.length() << endl;
	cout << "Длина списка list1 = " << list1.length() << endl;
	for (size_t i = 0; i < list1.length(); i++)
		cout << "Элемент списка list1 №" << i << ": " << list1[i].GetValue() << endl;
	
	cout << "Стек." << endl;
	cout << "Поместим в bs элементы 123, 444, 555." << endl;
	bs.push(123);
	bs.push(444);
	bs.push(555);

	cout << "Поместим в sb элементы 12, 44." << endl;
	sb.push(12);
	sb.push(44);

	cout << "Присоединим к bs sb." << endl;
	bs.join(sb);

	cout << "Поместим в bs элемент 888" << endl;
	bs.push(888);

	cout << "Выведем содержимое стека bs: " << endl;

	while (!bs.is_empty())
	{
		cout << bs.pop() << ' ';
	}

	cout << endl;

	return 0;
}