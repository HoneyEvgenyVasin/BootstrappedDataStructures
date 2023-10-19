#pragma once

#include "outofrange.h"

#include <iostream>

using std::cout;
using std::endl;

template <class T>
class StackNode
{
private:
	T info;
	StackNode<T>* next;
public:
	//Конструкторы
	StackNode()
	{
		next = NULL;
	}
	StackNode(T _info) : info(_info), next(NULL){}

	//Сеттеры-геттеры
	void SetValue(T _info) { info = _info; }
	void SetNext(StackNode* _next) { next = _next; }
	T& GetValue() { return info; }
	StackNode<T>* GetNext() { return next; }
};


//Обычный стек
template<class T>
class TStack
{
private:
	StackNode<T>* _top = nullptr;
	size_t len = 0;
public:
	TStack() {}
	TStack(T value)
	{
		StackNode<T>* node = new StackNode<T>(value);
		_top = node;
		len = 1;
	}

	StackNode<T>* top() { return _top; }
	bool is_empty() { return _top == nullptr; }
	size_t length() { return len; }
	void push(StackNode<T>* NewNode)
	{
		if (_top == nullptr)
			_top = NewNode;
		else
		{
			NewNode->SetNext(_top);
			_top = NewNode;
		}
		++len;
	}

	void push(T& value)
	{
		StackNode<T>* node = new StackNode<T>(value);
		push(node);
	}

	void push_const(T value)
	{
		StackNode<T>* node = new StackNode<T>(value);
		push(node);
	}

	StackNode<T>* pop()
	{
		StackNode<T>* result = _top;
		
		_top = _top->GetNext();
		--len;
		return result;
	}

	T pop_val()
	{
		T result;
		StackNode<T>* p = pop();
		
		result = p->GetValue();
		delete[] p;
		return result;
	}
};

//БУТСТРАПИЗИРОВАННЫЙ СТЕК
template<class T>
class BootstrappedStack
{
private:
	TStack<T> values;
	TStack<BootstrappedStack<T>&> stack;

public:
	BootstrappedStack() { 
		stack.push(*this); }
	TStack<T>& GetValues() { return values; }
	void push(T value)
	{
		stack.top()->GetValue().values.push(value);
	}

	T pop()
	{
		is_empty();
		if (stack.top()->GetValue().values.is_empty())
			stack.pop();
		return stack.top()->GetValue().values.pop_val();
	}

	bool is_empty() 
	{
		BootstrappedStack<T>& l = stack.top()->GetValue();
		return (&l == this) && stack.top()->GetValue().values.is_empty();
	}

	void join(BootstrappedStack<T>& second_stack)
	{
		stack.push(second_stack);
	}
};