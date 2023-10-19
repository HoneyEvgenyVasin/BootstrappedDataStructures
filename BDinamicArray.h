#pragma once

#include <cstdlib>
#include <string>
#include <iostream>

#include "outofrange.h"

using std::cout;
using std::endl;

template<class T>
class DinamicArray
{
private:
	T* data;
	size_t _size;//‘‡ÍÚË˜ÂÒÍËÈ ‡ÁÏÂ 
	size_t capacity;//–Â‡Î¸Ì˚È ‡ÁÏÂ

	void resize()
	{
		capacity = capacity ? capacity * 2 : 1;
		T* new_data = new T[capacity];
		std::copy(data, data + _size, new_data);
		delete[] data;
		data = new_data;
	}
public:
	DinamicArray() : data(nullptr), _size(0), capacity(0) {}
	~DinamicArray()
	{
		clear();
	}
	
	void clear()
	{
		delete[] data;
		data = nullptr;
		_size = capacity = 0;
	}

	void push_back(T new_elem)
	{
		if (_size == capacity)
			resize();
		data[_size++] = new_elem;
	}

	T& operator[](size_t index)
	{
		if(index >= _size)
			throw new OutOfRangeException{ "OutOfRange in Dinamic Array!!!" };
		return data[index];
	}

	size_t size() { return _size; }
};

//¡”“—“–¿œ»«»–Œ¬¿ÕÕ€… ƒ»Õ¿Ã»◊≈— »… Ã¿——»¬
template <class T>
class BDinamicArray
{
private:
	DinamicArray<T> data;
	DinamicArray<BDinamicArray*> pool;

	T* get(size_t n, size_t& count)
	{
		T* p = nullptr;

		for (int i = 0; i < data.size(); i++, count++)
		{
			if (count == n)
				return &data[i];
		}
	
		for (int j = 0; j < pool.size(); j++)
		{
			BDinamicArray<T>* ptr = pool[j];

			p = ptr->get(n, count);
			if (p != nullptr)
				break;
		}

		return p;
	}

public:
	BDinamicArray()
	{}

	BDinamicArray(T value)
	{
		data.push_back(value);
	}
	~BDinamicArray()
	{
		pool.clear();
		data.clear();
	}

	T& operator[](size_t index)
	{
		return get(index);
	}

	T& get(size_t n)
	{
		size_t count = 0;
		if(n > this->length())
			throw new OutOfRangeException{ "OutOfRange!!!" };
		return *get(n, count);
	}

	void join(BDinamicArray<T> *da)
	{
		pool.push_back(da);
	}

	void push(T new_value)
	{
		if (!pool.size())
			this->data.push_back(new_value);
		else
		{
			pool[pool.size() - 1]->data.push_back(new_value);
		}
	}

	size_t length() 
	{ 
		size_t total_length = this->data.size();
		for (size_t i = 0; i < pool.size(); i++)
		{
			total_length += pool[i]->length();
		}
		return total_length;
	}

};

template<class T>
class BootstrappedDinamicArray
{
private:
	BDinamicArray<T> array;
	BootstrappedDinamicArray<T>* last = this;
public:
	BootstrappedDinamicArray(){}
	BootstrappedDinamicArray(T value)
	{
		array.push(value);
	}

	BDinamicArray<T>* GetArray() { return &this->array; }
	T& get(size_t n) { return array.get(n); }
	T& operator[](size_t n) { return array[n]; }
	size_t length() { return array.length(); }
	void join(BootstrappedDinamicArray<T>& da)
	{
		array.join(da.GetArray());
		last = &da;
	}
	void push(T value)
	{
		last->array.push(value);
	}
};

