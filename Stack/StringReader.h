#pragma once

#include <string.h>
#include <iostream>

class StringReader
{
private:
	char* m_data;
	int m_currSize;
	int m_maxSize;

public:
	StringReader(const char* s)
	{
		m_currSize = strlen(s);
		m_maxSize = m_currSize + 10;

		m_data = new char[m_maxSize + 1]();
		strcpy(m_data, s);
	}
	~StringReader()
	{
		delete[] m_data;
	}

	void push_back(char c)
	{
		if (m_currSize >= m_maxSize)
			resize(2 * m_maxSize);

		m_data[m_currSize++] = c;
	}

	friend std::ostream& operator<<(std::ostream& output, const StringReader& str)
	{
		std::cout << str.m_data << '\n';

		return output;
	}

private:
	void resize(int new_size)
	{
		//std::cout << "Resizing\n";

		char* pom = new char[m_currSize + 1]();
		strcpy(pom, m_data);

		delete[] m_data;
		m_maxSize = new_size;
		m_data = new char[m_maxSize + 1]();

		strcpy(m_data, pom);
	}

};

