#pragma once
#include "Stack.h"
#include "String.h"

class IzrazValidator
{
private:
	Stack<int> m_operands;
	Stack<char> m_operators;
	String m_izraz;
	int m_index = 0;

public:
	IzrazValidator(const String& izraz): m_izraz(izraz) {}
	~IzrazValidator() {}

	bool validate()
	{
		int lenght = m_izraz.length();

		bool valid = true;
		try
		{
			for (int i = 0; i < lenght; i++)
			{
				if (m_izraz[i] == '(' || m_izraz[i] == '[' || m_izraz[i] == '{')
				{
					m_operands.push(m_izraz[i]);
				}
				else if (m_izraz[i] == ')' || m_izraz[i] == ']' || m_izraz[i] == '}')
				{
					if (m_operands.pop() != match(m_izraz[i]))
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

		if (m_operands.is_empty() && valid)
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

