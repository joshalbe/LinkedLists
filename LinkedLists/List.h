#pragma once
#include "Iterator.h"
#include <iostream>

template <typename T>
class List
{
public:
	List() {};
	List(List<T>& otherList);

	Iterator<T> begin() const;
	Iterator<T> end() const;
	void destroy();
	void pushFront(const T& value);
	void pushBack(const T& value);
	bool insert(const T& value, int index);
	bool remove(const T& value);
	void sort();
	void print() const;
	void initialize();
	bool contains(const T& object);
	bool isEmpty() const;
	bool getData(Iterator<T>& iter, int index);
	int getLength() const;
	void operator =(const List<T>& otherList);

private:
	Node<T>* m_first, m_head = Node<T>();
	Node<T>* m_last, m_tail = Node<T>();
	int m_nodeCount = 0;
};

template<typename T>
inline List<T>::List(List<T>& otherList)
{
	this = otherList;
}

template<typename T>
inline Iterator<T> List<T>::begin() const
{
	return Iterator<T>(m_first);
}

template<typename T>
inline Iterator<T> List<T>::end() const
{
	return Iterator<T>(m_last);
}

template<typename T>
inline void List<T>::destroy()
{
	for (Iterator<T> iter = begin(); iter != end(); ++iter)
	{
		remove(iter.m_current);
	}
}

template<typename T>
inline void List<T>::pushFront(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_first->previous = newNode;
	newNode->next = m_first;

	newNode->previous = nullptr;
	m_first = newNode;

	m_nodeCount++;

	if (m_nodeCount == 1)
	{
		m_last = newNode;
	}
	else if (m_nodeCount == 2)
	{
		m_last = newNode->next;
	}
}

template<typename T>
inline void List<T>::pushBack(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_last->next = newNode;
	newNode->previous = m_last;
	newNode->next = nullptr;
	m_last = newNode;

	m_nodeCount++;

	if (m_nodeCount == 1)
	{
		m_first = newNode;
	}
	else if (m_nodeCount == 2)
	{
		m_first = newNode->previous;
	}
}

template<typename T>
inline bool List<T>::insert(const T& value, int index)
{
	Iterator<T> iterator = begin();
	for (int i = 0; i < index; i++)
	{
		iterator++;
	}

	Node<T> newNode = new Node<T>(value);

	newNode.previous = iterator.m_current.previous;
	newNode.next = iterator.m_current;

	iterator.m_current.previous->next = newNode;
	iterator.m_current.previous = newNode;

	newNode.previous = newNode;

	if (iterator.m_current == m_first)
	{
		m_first = newNode;
	}

	if (iterator.m_current == m_last)
	{
		m_last = newNode;
	}

	m_nodeCount++;
	return true;
}

template<typename T>
inline bool List<T>::remove(const T& value)
{
	Iterator<T> iter = Iterator<T>();
	for (Iterator<T> iterator = begin(); iterator != end(); ++iterator)
		if (contains(value))
		{
			if (iterator == m_first)
			{
				m_first = iterator--;
			}
			iterator.m_current.next.previous = iterator.m_current.previous;
			iterator.m_current.next = iterator.m_current.next;

			delete(iterator.m_current);
			m_nodeCount--;
			return true;
		}
	return false;
}

template<typename T>
inline void List<T>::sort()
{
	Iterator<T> iterator = begin();
	Iterator<T> iterator2 = end();
	for (int i = 0; i < getLength(); i++)
	{
		for (int j = getLength() - 1; j > i; j--)
		{
			getData(iterator, j - 1);
			getData(iterator2, j);
			if (*iterator2 < *iterator)
			{
				Iterator<T> temp;
				temp = iterator2;
				iterator2 = iterator;
				iterator = temp;
			}
		}
	}
}

template<typename T>
inline void List<T>::print() const
{
	for (Iterator<T> iterator = begin(); iterator != end(); iterator = iterator++)
	{
		std::cout << *iterator << " ";
	}
	std::cout << std::endl;
}

template<typename T>
inline void List<T>::initialize()
{
	m_first = new Node<T>();
	m_last = new Node<T>();
	m_nodeCount = 0;
}

template<typename T>
inline bool List<T>::contains(const T& object)
{
	for (int i = 0; i < getLength(); i++)
	{
		if (i == object)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool List<T>::isEmpty() const
{
	return (!m_first);
}

template<typename T>
inline bool List<T>::getData(Iterator<T>& iterator, int index)
{
	iterator = begin();

	for (int i = 0; i < index; i++)
	{
		iterator = iterator++;
	}

	return false;
}

template<typename T>
inline int List<T>::getLength() const
{
	return m_nodeCount;
}

template<typename T>
inline void List<T>::operator=(const List<T>& otherList)
{
	Iterator<T> tempIterator = new Iterator<T>(begin());
	Iterator<T> tempIterator2 = new Iterator<T>(otherList->m_first);
	while (tempIterator.m_current != otherList.m_last)
	{
		for (int i = 0; i < otherList->getLength(); i++)
		{
			tempIterator->m_current = tempIterator2->m_current;
		}
	};
}