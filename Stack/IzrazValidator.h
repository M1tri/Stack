#pragma once
#include "Stack.h"
#include <string>

class IzrazValidator
{
private:
	Stack<int> operands;
	Stack<char> operators;
	char* izraz;
	int index = 0;

public:
	IzrazValidator(const char* izraz)
	{
		this->izraz = new char[len(izraz) + 1]();

		for (int i = 0; i < len(izraz); i++)
			this->izraz[i] = izraz[i];
	}
	~IzrazValidator()
	{
		delete[] izraz;
	}

	bool validate()
	{
		int lenght = len(izraz);

		bool valid = true;
		try
		{
			for (int i = 0; i < lenght; i++)
			{
				if (izraz[i] == '(' || izraz[i] == '[' || izraz[i] == '{')
				{
					operands.push(izraz[i]);
				}
				else if (izraz[i] == ')' || izraz[i] == ']' || izraz[i] == '}')
				{
					if (operands.pop() != match(izraz[i]))
					{
						valid = false;
						break;
					}
				}
			}
		}
		catch (...)
		{
			valid = false;
		}

		if (operands.is_empty() && valid)
			return true;
		else
			return false;
	}

private:
	int len(const char* s) const
	{
		int i = 0;
		while (s[i++])
			;;

		return i - 1;
	}
	char match(char c) const
	{
		if (c == ')')
			return '(';
		else if (c == ']')
			return '[';
		else if (c == '}')
			return '{';
		else
			return 0;
	}
};

