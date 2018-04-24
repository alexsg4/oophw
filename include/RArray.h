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

	void removeMultiple(unsigned *iArr, const unsigned size);

private:
	void _swap(T &a, T &b);
	
	inline int left(int i) const { return 2 * i + 1; }
	inline int right(int i) const { return 2 * i + 2; }

	void maxHeapify(unsigned m, int i);
	void minHeapify(unsigned m, int i);
	void buildMaxHeap();
	void buildMinHeap();

	static unsigned tIndex;

	//TODO implement
	bool _findIndexIn(const unsigned index, unsigned arr[]) {};

public:
	void sort();

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
		for (unsigned i = 0; i<m_size; i++)
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
	if (isEmpty()) { return;  }
	for (unsigned i = from; i < m_capacity; i++)
	{
		members[i] = nullptr;
	}
}

template <class T>
void RArray<T>::erase()
{
	for (unsigned i = 0; i < m_size; i++)
	{
		delete members[i];
		members[i] = nullptr;
	}
	m_size = 0;
	_initialise();
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
	if (m_size <= id)
	{
		out << "Nu se poate sterge elementul de pe pozitia " << id << ". \n";
		return;
	}

	delete members[id];
	for (unsigned i = id; i < m_size - 1; i++)
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
		expand(m_size * 2);
	}

	members[m_size++] = new T(element);
}

template<class T>
void RArray<T>::add()
{
	if (m_size >= m_capacity)
	{
		expand(m_size * 2);
	}

	members[m_size++] = new T();
}

template<class T>
RArray<T>& RArray<T>::operator+=(const T & element)
{
	if (m_size >= m_capacity)
	{
		expand(m_size * 2);
	}
	members[m_size++] = new T(element);

	return *this;
}

template<class T>
unsigned RArray<T>::tIndex = 0;

template<class T>
void RArray<T>::removeMultiple(unsigned *iArr, const unsigned size)
{
	//TODO treat case where iArr.size > m_size

	//TODO sort iArr

	if (!iArr) { return; }

	//count elements to remove
	unsigned removed = 0;
	for (unsigned i = 0; i < size; i++)
	{
		if (iArr[i] < m_size)
		{
			removed++;
		}
	}

	//store indexes for elements to keep
	if (removed < m_size)
	{
		unsigned *temp = new unsigned[m_size - removed]();

		T** tempMembers = new T*[m_size];

		//collect indexes of elements to keep in the array
		for (unsigned i = 0; i < m_size; i++)
		{
			bool isOK = true;
			//check each index against the ones we will remove
			//TODO use binary search since input will be sorted
			for (unsigned j = 0; j < size; j++)
			{
				if (i == iArr[j])
				{
					isOK = false;
					break;
				}
			}
			if (isOK)
			{
				tempMembers[tIndex++] = members[i];
			}
			
		}

		delete[] members;
		members = tempMembers;
		m_size = tIndex;
		
		delete[] temp;
	}
	
	else { erase(); };

	tIndex = 0;
}

template <class T>
void RArray<T>::_swap(T& a, T& b)
{
	T aux(a);
	a = b;
	b = aux;
}

template <class T>
void RArray<T>::maxHeapify(unsigned m, int i)
{
	int iMax = i;
	int l = left(i);
	int r = right(i);

	if (l<m && *members[l] > *members[iMax]) { iMax = l; }
	if (r<m && *members[r] > *members[iMax]) { iMax = r; }

	if (iMax != i)
	{
		_swap(*members[i], *members[iMax]);
		maxHeapify(m, iMax);
	}
}

template <class T>
void RArray<T>::minHeapify(unsigned m, int i)
{
	int iMin = i;
	int l = left(i);
	int r = right(i);

	if (l<m && *members[l] < *members[iMin]) { iMin = l; }
	if (r<m && *members[r] < *members[iMin]) { iMin = r; }

	if (iMin != i)
	{
		_swap(*members[i], *members[iMin]);
		minHeapify(m, iMin);
	}
}

template <class T>
void RArray<T>::buildMaxHeap()
{
	int n = static_cast<int> (m_size);
	for (int i = n / 2 - 1; i >= 0; i--) { maxHeapify(n, i); }
}

template <class T>
void RArray<T>::buildMinHeap()
{
	int n = static_cast<int>(m_size);
	for (int i = n / 2 - 1; i >= 0; i--) { minHeapify(n, i); }
}

template <class T>
void RArray<T>::sort()
{
	buildMaxHeap();
	int n = static_cast<int> (m_size);

	for (int i = n - 1; i >= 0; i--)
	{
		_swap(*members[0], *members[i]);
		maxHeapify(i, 0);
	}
}
