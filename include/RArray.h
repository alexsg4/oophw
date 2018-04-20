#pragma once
#include <iostream>

//specialized container class 
template <class T>
class RArray
{
private:
	unsigned m_capacity = 2;	//maximum capacity
	unsigned m_size = 0;		//current size 
	T** members;
	
	//Zeroes out a sub-array of members
	void _initialise(const unsigned& from = 0);

public:
	RArray();
	RArray(const unsigned cap);
	RArray(const RArray &src);

	//Copies over another fleet and discards previous members
	RArray& operator=(const RArray& src);
	
	//Returns member at position id, assuming it exists
	T& operator[](const unsigned id) const;

	//Removes all elements and nullify positions
	void erase();

	//Expands list capacity
	void expand(unsigned newCapacity);

	inline const bool isEmpty() const { return (m_size == 0); }
	inline const unsigned size() const { return m_size; }
	inline const unsigned capacity() const { return m_capacity; }

	~RArray();
	
	//concatenates two arrays
	RArray& operator+(const RArray& src);
	
	//removes an element by it's position
	void removeById(const unsigned id, std::ostream& out = std::cout);

	//add pre-built element
	void add(const T & element);
	RArray& operator+=(const T & element);
	//add container
	void add();
};

template <class T>
RArray<T>::RArray()
{
	members = new T*[m_capacity];
	_initialise();
}

template <class T>
RArray<T>::RArray(const unsigned cap) : m_capacity(cap)
{
	members = new T*[m_capacity];
	_initialise();
}

template <class T>
RArray<T>::RArray(const RArray &src)
{
	m_capacity = src.m_capacity;
	m_size = src.m_size;
	
	members = new T*[m_capacity];
	_initialise();

	for (unsigned i = 0; i < m_size; i++)
	{
		members[i] = src.members[i]; 
	}
}

template <class T>
RArray<T>& RArray<T>::operator=(const RArray& src)
{
	if (m_capacity < src.m_size)
	{
		m_capacity = src.m_capacity;
		T** expanded = new T*[m_capacity];
		
		m_size = src.m_size;
		for(unsigned i=0; i<m_size; i++)
		{
			expanded[i] = src.members[i];
		}

		delete[] members;
		members = expanded;
		_initialise(m_size);
	}

	else
	{
		erase();
		m_size = src.m_size;
		for (unsigned i = 0; i<m_size; i++)
		{
			members[i] = src.members[i];
		}
	}

	return *this;
}

template <class T>
T& RArray<T>::operator[](const unsigned id) const
{
	if (id >= m_size || id < 0 || m_size == 0)
	{
		throw "OUT OF BOUNDS!";
	}

	return *members[id];
}

template <class T>
void RArray<T>::_initialise(const unsigned& from)
{
	for (unsigned i = from; i < m_capacity; i++)
	{
		members[i] = nullptr;
	}
}

template <class T>
void RArray<T>::erase()
{
	for (unsigned i = 0; i < m_capacity; i++)
	{
		if (members[i])
		{ 
			delete members[i];
		}
		members[i] = nullptr;
	}
	m_size = 0;
}

template<class T>
void RArray<T>::expand(unsigned newCapacity)
{
	//if expansion is not necessary
	if (newCapacity <= m_capacity) { return; }

	m_capacity = newCapacity;
	
	T** expanded = new T*[m_capacity];

	for (unsigned i = 0; i < m_size; i++)
	{
		expanded[i] = members[i];
	}
	
	delete[] members;

	members = expanded;
	_initialise(m_size);
}

template<class T>
RArray<T>::~RArray()
{
	for (unsigned i = 0; i < m_size; i++) { delete members[i]; }
	if (m_size)
	{
		delete[] members;
	}
}

template<class T>
RArray<T>& RArray<T>::operator+(const RArray& src)
{
	if (m_capacity - m_size < src.m_size)
	{
		m_capacity = m_size + src.m_size;
		expand(m_capacity);
	}

	for (unsigned i = 0; i < src.m_size; i++)
	{
		members[m_size + i] = src.members[i];
	}
	m_size += src.m_size;

	return *this;
}

template<class T>
void RArray<T>::removeById(const unsigned id, std::ostream& out)
{
	if(m_size <= id) 
	{
		out << "Nu se poate sterge elementul de pe pozitia " << id << ". \n";
		return;
	}

	delete members[id];
	for (unsigned i = 0; i < m_size-1; i++)
	{
		members[i] = members[i + 1];
	}
	members[--m_size] = nullptr;
}

template<class T>
void RArray<T>::add(const T & element)
{
	if (m_size >= m_capacity)
	{
		expand(m_size*2);
	}

	members[m_size++] = new T(element);
}

template<class T>
void RArray<T>::add()
{
	if (m_size >= m_capacity)
	{
		expand(m_size *2);
	}

	members[m_size++] = new T();
}

template<class T>
RArray<T>& RArray<T>::operator+=(const T & element)
{
	if (m_size >= m_capacity)
	{
		expand(m_size *2);
	}
	members[m_size++] = new T(element);
	
	return *this;
}
