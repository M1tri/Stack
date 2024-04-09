#pragma once

#include "Stack.h"
#include <string>
#include <iostream>

class Sabirator
{
private:
	Stack<char> num1;
	Stack<char> num2;
	Stack<char> rez;
	int cout;

public:
	Sabirator(const char* num1, const char* num2)
	{
		int l1 = len(num1);
		int l2 = len(num2);

		for (int i = 0; i < l1; i++)
		{
			this->num1.push(num1[i]);
		}

		for (int i = 0; i < l2; i++)
		{
			this->num2.push(num2[i]);
		}
	}

	void load(const char* num1, const char* num2)
	{
		int l1 = len(num1);
		int l2 = len(num2);

		while (!this->num1.is_empty())
			this->num1.pop();

		while (!this->num2.is_empty())
			this->num2.pop();

		while (!this->rez.is_empty())
			this->rez.pop();

		for (int i = 0; i < l1; i++)
		{
			this->num1.push(num1[i]);
		}

		for (int i = 0; i < l2; i++)
		{
			this->num2.push(num2[i]);
		}
	}

	void add()
	{
		int carry = 0;
		while (!num1.is_empty() && !num2.is_empty())
		{
			char c_digit1 = num1.pop();
			char c_digit2 = num2.pop();

			int rez = ctoi(c_digit1) + ctoi(c_digit2) + carry;

			char s = dtoc(rez % 10);
			carry = (rez / 10) % 10;

			this->rez.push(s);
		}

		Stack<char>* leftover = nullptr;

		if (num1.is_empty() && !num2.is_empty())
		{
			leftover = &num2;

		}
		else if (num2.is_empty() && !num1.is_empty())
		{
			leftover = &num1;
		}

		if (leftover != nullptr)
		{
			while (!leftover->is_empty())
			{
				int rez = ctoi(leftover->pop()) + carry;

				char s = dtoc(rez % 10);
				carry = (rez / 10) % 10;

				this->rez.push(s);
			}
		}

		cout = carry;
	}

	void show_rez()
	{
		std::cout << "The result is:\n";
		std::cout << cout;

		while (!this->rez.is_empty())
		{
			std::cout << rez.pop();
		}
		std::cout << '\n';
	}

private:

	int len(const char* s) const
	{
		int i = 0;
		while (s[i++])
			;;

		return i - 1;
	}

	// char -> int
	int ctoi(char c)
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

	// digit -> char
	int dtoc(int digit)
	{
		switch (digit)
		{
		case 0:
			return '0';
			break;
		case 1:
			return '1';
			break;
		case 2:
			return '2';
			break;
		case 3:
			return '3';
			break;
		case 4:
			return '4';
			break;
		case 5:
			return '5';
			break;
		case 6:
			return '6';
			break;
		case 7:
			return '7';
			break;
		case 8:
			return '8';
			break;
		case 9:
			return '9';
			break;
		default:
			return '\0';
		}
	}

};

