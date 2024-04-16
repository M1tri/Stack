#pragma once

#include <iostream>
#include <math.h>

class String
{
private:
	char* m_data;
	int m_cur_length;
	int m_max_length;

public:
	String()
	{
		m_max_length = 10;
		m_cur_length = 0;
		m_data = new char[m_max_length + 1]();
	}
	String(const char* data)
	{
		m_cur_length = my_strlen(data);
		m_max_length = m_cur_length + 10;
		m_data = new char[m_max_length + 1]();
		my_strcpy(m_data, data);
	}
	String(const String& s)
	{
		m_max_length = s.m_max_length;
		m_cur_length = s.m_cur_length;
		m_data = new char[m_max_length + 1]();
		my_strcpy(m_data, s.m_data);
	}
	~String()
	{
		delete[] m_data;
	}

	int length() const
	{
		return m_cur_length;
	}

	void push_back(char c)
	{
		if (m_cur_length >= m_max_length)
		{
			resize(2 * m_max_length);
		}

		m_data[m_cur_length++] = c;
	}

	char pop_back()
	{
		if (m_cur_length <= 0)
			return '\0';

		return m_data[--m_cur_length];
	}

	void append(const char* s)
	{
		int l = my_strlen(s);

		for (int i = 0; i < l; i++)
		{
			push_back(s[i]);
		}
	}

	void append(const String& s)
	{
		append(s.m_data);
	}

	void print(std::ostream& output = std::cout) const
	{
		output << m_data;
	}

	bool operator==(const String& s) const
	{
		return my_strcmp(m_data, s.m_data);
	}

	void clear()
	{
		for (int i = 0; i < m_cur_length; i++)
			m_data[i] = '\0';

		m_cur_length = 0;
	}

	String& operator=(const String& s)
	{
		if (&s != this)
		{
			delete[] m_data;

			m_max_length = s.m_max_length;
			m_cur_length = s.m_cur_length;
			m_data = new char[m_max_length + 1]();
			my_strcpy(m_data, s.m_data);
		}

		return *this;
	}

	String& operator=(const char* s)
	{
		delete[] m_data;

		m_cur_length = my_strlen(s);
		m_max_length = m_cur_length + 10;
		m_data = new char[m_max_length + 1]();
		my_strcpy(m_data, s);

		return *this;
	}

	char operator[](const int index) const
	{
		return m_data[index];
	}

	String& operator+(char c) const
	{
		String* novi = new String(*this);
		novi->push_back(c);

		return *novi;
	}

	String& operator+(const char* s) const
	{
		String* novi = new String(*this);
		novi->append(s);

		return *novi;
	}

	String& operator+(const String& s) const
	{
		String novi = *this;
		novi.append(s.m_data);

		return novi;
	}

	String& operator+=(char c)
	{
		push_back(c);

		return *this;
	}

	String& operator+=(const char* s)
	{
		append(s);

		return *this;
	}
	
	String& operator+=(const String& s)
	{
		append(s.m_data);

		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream& output, const String& s)
	{
		s.print(output);

		return output;
	}

private:
	int my_strlen(const char* s) const
	{
		int i = 0;
		while (s[i] != '\0')
		{
			i++;
		}

		return i; 
	}

	int my_strcpy(char* dst, const char* src)
	{
		int l1 = my_strlen(src);

		int i;
		for (i = 0; i < l1 && src[i] != '\0'; i++)
		{
			dst[i] = src[i];
		}
		dst[i] = '\0';

		return i - 1;
	}

	bool my_strcmp(const char* s1, const char* s2) const
	{
		int l1 = my_strlen(s1);
		int l2 = my_strlen(s2);

		if (l1 != l2)
			return false;

		for (int i = 0; i < l1; i++)
		{
			if (s1[i] != s2[i])
				return false;
		}

		return true;
	}

	void resize(int new_size)
	{
		m_max_length = new_size;

		char* pom = new char[m_cur_length + 1]();
		my_strcpy(pom, m_data);
		delete[] m_data;

		m_data = new char[m_max_length + 1]();
		my_strcpy(m_data, pom);

		delete[] pom;
	}
};


namespace mitri
{
	static int ctoi(char c)
	{
		switch (c)
		{
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
		case '8':
			return 8;
			break;
		case '9':
			return 9;
			break;
		default:
			return -1;
		}
	}

	static int Stoi(const String& s)
	{
		int len = s.length();
		int result = 0;

		bool negative = false;
		for (int i = len - 1; i >= 0; i--)
		{
			if (!isdigit(s[i]))
			{
				if (i == 0 && s[i] == '-')
				{
					negative = true;
					continue;
				}
				
				return -1;
			}

			result += ctoi(s[i]) * pow(10, len - 1 - i);
		}

		if (negative)
			result = -result;

		return result;
	}

	static bool is_digit(char c)
	{
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return true;
		default:
			return false;
		}
	}

	static bool is_operator(char c)
	{
		switch (c)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
		}
	}

	// op1 > op2 ? po prioritetu
	static bool cmp_operator(char op1, char op2)
	{
		if (op1 == '+' || op1 == '-')
		{
			return false;
		}
		else if (op1 == '*' || op1 == '/')
		{
			if (op2 == '+' || op2 == '-')
				return true;
			else
				return false;
		}
	}
}