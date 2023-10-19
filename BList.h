#pragma once

#include "outofrange.h"

#define BL_DEBUG

#ifdef BL_DEBUG
#include <iostream>

using std::cout;
using std::endl;
#endif

template <class T>
class ListNode
{
private:
	T info;
	ListNode<T> *next;
public:
	//������������
	ListNode()
	{
		next = NULL;
	}
	ListNode(T _info): info(_info), next(NULL){}

	//�������-�������
	void SetValue(T _info) { info = _info; }
	void SetNext(ListNode* _next) { next = _next; }
	T GetValue() { return info; }
	ListNode<T>* GetNext() { return next; }
};

//������� ������
template<class T>
class TList
{
private:
	ListNode<T>* list;
	ListNode<T>* last; //��������� �� ��������� ������� ������
	size_t iterator; //��� ������ ������ GetNextInfo ����� ���������� ���������� ���� � ������� ������ ����������� ���� ����������
	size_t len;
public:
	TList(): list(NULL), iterator(0), len(0){}
	TList(T first_elem)
	{
		list = new ListNode<T>(first_elem);
		iterator = 0;
		len = 1;
	}

	//���������� ������ ��������
	void AddElem(T NewNodeInfo)
	{
		ListNode<T>* ptr = new ListNode<T>(NewNodeInfo);

		this->last = ptr;

		if (this->list == NULL)
			list = ptr;
		else
		{
			ListNode<T>* it = this->list;
			while (it->GetNext() != NULL)
			{
				it = it->GetNext();
			}
			it->SetNext(ptr);
		}

		++len;
	}

	//��������� �������� �����
	void GoToFirst() { iterator = 0; }
	//���������� ����� ������
	size_t GetLength() { return len; }
	//���� ��������� ��� �������� ������, ������ false, ����� true
	bool IsBottom()
	{
		if (iterator == this->GetLength())
			return true;
		return false;
	}
	//����� ����������� ����(iterator)
	T GetNextInfo()
	{
		size_t count = 0;
		ListNode<T>* ptr = this->list;
		T node_info;

		while (count != iterator)
		{
			ptr = ptr->GetNext();
			++count;
		}

		node_info = ptr->GetValue();
		++iterator;
		return node_info;
	}
	//����� ����������� ���� � ������� index
	T GetItemInfoByIndex(size_t indx)
	{
		ListNode<T>* ptr = this->list;

		for (size_t i = 0; i != indx; i++)
			ptr = ptr->GetNext();
		return ptr->GetValue();
	}

	//���������� ���� � ������� indx
	ListNode<T>* GetItemByIndex(size_t indx)
	{
		ListNode<T>* ptr = this->list;

		for (size_t i = 0; i != indx; i++)
			ptr = ptr->GetNext();
		return ptr;
	}

	//����������� ����������� ���� � ������� index
	void SetItemInfoByIndex(size_t index, T NewValue)
	{
		ListNode<T>* ptr = this->list;

		for (unsigned int i = 0; i != index; i++)
			ptr = ptr->GetNext();
		ptr->SetValue(NewValue);
	}
	//����� ��������� �� ������ ����
	ListNode<T>* GetFirstNode() { return list; }
	//�������� ���� �� ������� indx
	void RemoveItemByIndex(size_t indx)
	{
		ListNode<T>* ptrNodeForRem = this->list;
		ListNode<T>* ptrPrevNode = NULL;
		ListNode<T>* ptrNextNode = NULL;

		if (indx == 0)
		{
			ListNode<T>* tmp = ptrNodeForRem;
			this->list = tmp->GetNext();
			delete ptrNodeForRem;
			--len;
			return;
		}

		for (size_t count = 0; count <= indx; count++)
		{
			if (count == indx)
			{
				ListNode<T>* tmp = ptrNodeForRem->GetNext();//� tmp ����� �������� ����� ���������� ����
				
				ptrPrevNode = ptrNodeForRem;
				ptrNextNode = tmp->GetNext();
				delete tmp;
				ptrPrevNode->SetNext(ptrNextNode);
				--len;
				return;
			}
			ptrNodeForRem = ptrNodeForRem->GetNext();
		}
	}
};

//������������������� ������
template<class T>
class BList
{
private:
	TList<T>* list;//������
	BList<T>* tail;//��������� �� ��������� ������
	BList<T>* head;//��������� �� ������ ������
	BList<T>* next;//��������� �� ��������� ������

	void init()
	{
		list = NULL; next = NULL;
		tail = this; head = this;
	}

public:
	BList() { init(); }
	//���������� � ������
	void push(T value)
	{
		BList<T>* ptrQueue = this;

		while (ptrQueue->next != NULL)
			ptrQueue = ptrQueue->next;
		if (ptrQueue->list == NULL)
			ptrQueue->list = new TList<T>(value);
		else
			ptrQueue->list->AddElem(value);
	}
	//������� �������
	void join(BList<T>* ptr)
	{
		tail->next = ptr;
	}

	//��������� �������� �� �������
	ListNode<T>* GetItemByIndex(size_t indx)
	{
		BList<T>* ptrQueue = this;
		size_t i = 0;

		while (ptrQueue != NULL)
		{
			TList<T>* ptrList = ptrQueue->list;

			for (size_t j = 0; j < ptrList->GetLength(); j++, i++)
			{
				if (i == indx)
					return ptrList->GetItemByIndex(j);
			}

			ptrQueue = ptrQueue->next;
		}
	}
	
	ListNode<T>& operator[](size_t n)
	{
		return *GetItemByIndex(n);
	}

	//����������� �������� �� �������
	void SetItemByIndex(size_t indx, T NewValue)
	{
		BList<T>* ptrQueue = this;
		size_t i = 0;

		while (ptrQueue != NULL)
		{
			TList<T>* ptrList = ptrQueue->list;

			for (int j = 0; j < ptrList->GetLength(); j++, i++)
			{
				if (i == indx)
				{
					ptrList->SetItemIndex(j, NewValue);
					return;
				}
			}
			ptrQueue = ptrQueue->next;
		}
	}

	//��������� ������� �������� �� ���������, ������ value. ���������� -1, ���� ����� �� ��� �����������
	long long find(T value)
	{
		BList<T>* ptrQueue = this;
		
		while (ptrQueue != NULL)
		{
			TList<T>* ptrList = ptrQueue->list;
			
			if (ptrList != NULL)
			{
				for (long long i = 0; i < ptrList->GetLength(); i++)
					if (value == ptrList->GetItemIndex(i))
						return i;
			}

			ptrQueue = ptrQueue->next;
		}
		return -1;
	}

	//���������� ���������� ��������� � ��������� ������
	size_t length()
	{
		BList<T>* ptr = head;
		size_t len = 0;
		size_t total_len = 0;

		while (ptr != NULL)
		{
			len += ptr->list->GetLength();
			ptr = ptr->next;
		}

		return len;
	}

	//�������� �������� �� �������
	void RemItemByIndex(size_t indx)
	{
		size_t count = 0;
		BList<T>* ptrQueue = this;

		while (ptrQueue != NULL)
		{
			TList<T>* ptrList = ptrQueue->list;

			if (ptrList != NULL)
			{
				for (size_t i = 0; i < ptrList->GetLength(); i++, count++)
				{
					if (count == indx)
					{
						ptrList->RemoveItemByIndex(i);
						return;
					}
				}
			}
			ptrQueue = ptrQueue->next;
		}
	}

#ifdef BL_DEBUG
	//����� ����������� ��������� ������ � stdout
	void dbgWalk()
	{
		BList<T>* ptrQueue = this;

		while (ptrQueue != NULL)
		{
			TList<T>* ptrList = ptrQueue->list;

			if (ptrList != NULL)
			{
				for (int i = 0; i < ptrList->GetLength(); i++)
					std::cout << ptrList->GetItemInfoByIndex(i) << std::endl;
			}
			ptrQueue = ptrQueue->next;
		}
	}
#endif
};

template<class T>
class BootstrappedList
{
private:
	BList<T> list;
public:
	BootstrappedList(){}
	BootstrappedList(T value) { list.push(value); }
	inline BList<T>* GetList() { return &this->list; }
	inline ListNode<T>* GetItemByIndex(size_t n) { return list.GetItemByIndex(n); }
	inline ListNode<T>& operator[](size_t n) { return *list.GetItemByIndex(n); }
	inline size_t length() { return list.length(); }
	inline void join(BootstrappedList<T>& lst){ list.join(lst.GetList()); }
	inline void push(T value) { list.push(value); }
};