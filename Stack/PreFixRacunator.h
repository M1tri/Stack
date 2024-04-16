#pragma once

#include <iostream>
#include "Stack.h"
#include <string>
#include "String.h"

class PreFixRacunator
{
private:
	Stack<int> m_operands;
	Stack<char> m_operators;
	String m_izraz;
	int m_index = 0;

public:
	PreFixRacunator(const char* izraz) : m_izraz(izraz) {}
	~PreFixRacunator() {}

	int calculate_prefix()
	{
		prepare_prefix();

		if (m_operands.is_empty() || m_operators.is_empty())
		{
			std::cout << "Zovi prepare_prefix majmune\n";
			return 0;
		}

		while (!m_operators.is_empty())
		{
			char op = m_operators.pop();

			if (op == '+')
			{
				int op2;
				int op1;

				try
				{
					op1 = m_operands.pop();
					op2 = m_operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 + op2;
				m_operands.push(rez);
			}
			else if (op == '-')
			{
				int op2;
				int op1;
				try
				{
					op1 = m_operands.pop();
					op2 = m_operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 - op2;
				m_operands.push(rez);
			}
			else if (op == '*')
			{
				int op2;
				int op1;
				try
				{
					op1 = m_operands.pop();
					op2 = m_operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 * op2;
				m_operands.push(rez);
			}
			else if (op == '/')
			{
				int op2;
				int op1;
				try
				{
					op1 = m_operands.pop();
					op2 = m_operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 / op2;
				m_operands.push(rez);
			}
		}


		int result = m_operands.pop();

		if (!m_operands.is_empty())
		{
			std::cout << "Sjebo si se :(\n";
		}

		return result;
	}

	char peek() const
	{
		if (m_index > m_izraz.length())
			return '\0';

		return m_izraz[m_index];
	}

	char consume()
	{
		return m_izraz[m_index++];
	}

private:
	int len(const char* s) const
	{
		int i = 0;
		while (s[i++])
			;;

		return i - 1;
	}
	void prepare_prefix()
	{
		int lenght = m_izraz.length();

		while (peek() != '\0' && !std::isdigit(peek()))
		{
			if (peek() == '/' || peek() == '*' || peek() == '+' || peek() == '-')
			{
				m_operators.push(consume());
			}
			else if (peek() == ' ')
			{
				consume();
			}
			else
			{
				exit(EXIT_FAILURE);
				std::cerr << "Nesto si sjebo\n";
			}
		}

		Stack<int> pom;
		while (peek() != '\0')
		{
			if (std::isdigit(peek()))
			{
				String buffer;
				buffer.push_back(consume());

				while (std::isdigit(peek()))
				{
					buffer.push_back(consume());
				}
				int n = mitri::Stoi(buffer);
				pom.push(n);
			}
			else if (peek() == ' ')
			{
				consume();
			}
			else
			{
				std::cerr << "Sjebo si se\n";
				exit(EXIT_FAILURE);
			}
		}

		while (!pom.is_empty())
		{
			m_operands.push(pom.pop());
		}

	}
};

