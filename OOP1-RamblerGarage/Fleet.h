#pragma once
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"

//specialized container class 
template <class T= >
class Fleet
{
private:
	unsigned m_capacity = 0;	//maximum capacity
	unsigned m_size = 0;		//current size 
	T** members;

public:
	Fleet() {};
	Fleet(const Fleet &src);

	Fleet& operator=(const Fleet& src);
	T& operator[](const unsigned id);

	//Zeroes out a sub-array of members
	void initialise(const unsigned& from);

	//Removes all elements and nullify positions
	void erase();
	void display();

	inline const bool isEmpty() const { return (size == 0); }
	inline const unsigned size() const { return m_size; }
	inline const unsigned capacity() const { return m_capacity; }

	~Fleet();

	//TODO implement
	
	//merges two fleets
	Fleet& operator+[const Fleet& src];
	
	//removes an element by it's position
	void removeById(const unsigned id, bool list = false);

	//adds a pre-built element
	void add(const T& element);

	//loads a number of vehicles from a file and applies random damage if necessary 
	void populate(unsigned elementsToAdd, bool applyDamage, const std::string& src ="", bool trim = true);
	
	//diagnostic for vehicles
	void diagnose();
	

};


template <class T>
Fleet<T>::Fleet(const unsigned cap) : m_capacity(cap)
{
	members = new T*[m_capacity];
	erase();
}

template <class T>
Fleet<T>::Fleet(const Fleet &src)
{
	m_capacity = src.m_capacity;
	m_size = src.m_size;
	
	members = new T*[m_capacity];
	erase();

	for (unsigned i = 0; i < m_size; i++)
	{
		members[i] = src->members[i]; 
	}
}

template <class T>
Fleet<T>::operator=(const Fleet& src)
{
	if (m_capacity < src.m_size)
	{
		m_capacity = src.m_capacity;
		T** expanded = new T*[m_capacity];
		
		m_size = src.m_size;
		for(unsigned i=0; i<m_size; i++)
		{
			expanded[i] = src->members[i];
		}

		delete[] members;
		members = expanded;
		initialise(m_size);
	}

	else
	{
		erase();
		m_size = src.m_size;
		for (unsigned i = 0; i<m_size; i++)
		{
			members[i] = src->members[i];
		}
	}
}

template <class T>
T& Fleet<T>::operator[](const unsigned id)
{
	if (id < size && size)
	{
		return &members[id];
	}

	else
	{
		//TODO
		//handle case
	}
}

template <class T>
void Fleet<T>::initialise(const unsigned& from)
{
	for (unsigned i = from; i < capacity; i++)
	{
		members[i] = nullptr;
	}
}

template <class T>
void Fleet<T>::erase()
{
	for (unsigned i = 0; i < m_capacity; i++)
	{
		if (members[i])
		{ 
			delete members[i];
		}
		members[i] = nullptr;
	}
	size = 0;
}

template <class T>
void Fleet<T>::display()
{
	for (unsigned i = 0; i < size; i++)
	{
		if (members[i]) { std::cout << members[i] << " "; }
	}
	std::cout << "\n";
}

template<class T>
Fleet<T>::~Fleet()
{
	for (unsigned i = 0; i < m_size; i++) { delete members[i]; }
	delete[] members;
}