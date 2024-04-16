#pragma once
#include <iostream>

// Dinamicki stack (al ne preko LL jer to je retardirano nego dinamicki ko std::vector)

template <typename T>
class Stack
{
private:
	int m_size;
	int m_top;
	T* m_data;

public:
	Stack(int size = 10) :m_size(size), m_top(-1)
	{
		m_data = new T[size]();
	}

	~Stack()
	{
		delete[] m_data;
	}

	bool push(T element)
	{
		if (m_top == m_size - 1)
		{
			resize(2 * m_size);
		}

		m_data[++m_top] = element;
		return true;
	}

	T pop()
	{
		if (m_top == -1)
			throw "Prazan stek\n";

		return m_data[m_top--];
	}

	T read_top() const
	{
		if (m_top == -1)
			throw "Prazan stek\n";

		return m_data[m_top];
	}

	bool is_empty() const
	{
		return m_top == -1;
	}

	// nema mnogo smisla jer je dinamicki al aj
	bool is_full() const
	{
		return m_top == (m_size - 1);
	}

	int curr_size() const
	{
		return m_top + 1;
	}

	void clear()
	{
		m_top = -1;
	}

private:

	void resize(int new_size)
	{
		T* pom = new T[new_size]();

		int limit = m_top + 1;

		if (new_size < m_top)
		{
			limit = new_size;
		}

		for (int i = 0; i < limit; i++)
		{
			pom[i] = m_data[i];
		}

		delete[] m_data;

		m_data = new T[new_size]();

		for (int i = 0; i < limit; i++)
		{
			m_data[i] = pom[i];
		}

		m_size = new_size;
		delete[] pom;
	}
};


