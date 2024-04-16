#pragma once

#include <iostream>
#include "Stack.h"
#include <string>
#include "String.h"

class PostFixRacunator
{
private:
	Stack<int> m_operands;
	Stack<char> m_operators;
	String m_izraz;
	int m_index = 0;

public:
	PostFixRacunator(const char* izraz) : m_izraz(izraz) {}
	PostFixRacunator(String izraz) : m_izraz(izraz) {}
	~PostFixRacunator() {}

	int calculate_postfix()
	{
		int length = m_izraz.length();

		String buffer;

		while (peek() != '\0')
		{
			if (std::isdigit(peek()))
			{
				buffer.push_back(consume());

				while (peek() != '\0' && std::isdigit(peek()))
				{
					buffer.push_back(consume());
				}

				int n = mitri::Stoi(buffer);
				m_operands.push(n);
				buffer.clear();
			}
			else if (peek() == ' ')
			{
				consume();
			}
			else if (peek() == '+')
			{
				int op2 = m_operands.pop();
				int op1 = m_operands.pop();

				int rez = op1 + op2;
				m_operands.push(rez);
				consume();
			}
			else if (peek() == '-')
			{
				int op2 = m_operands.pop();
				int op1 = m_operands.pop();

				int rez = op1 - op2;
				m_operands.push(rez);
				consume();
			}
			else if (peek() == '*')
			{
				int op2 = m_operands.pop();
				int op1 = m_operands.pop();

				int rez = op1 * op2;
				m_operands.push(rez);
				consume();
			}
			else if (peek() == '/')
			{
				int op2 = m_operands.pop();
				int op1 = m_operands.pop();

				int rez = op1 / op2;
				m_operands.push(rez);
				consume();
			}
			else
			{
				std::cerr << "Nesto si prijatelju zajebo\n";
				exit(EXIT_FAILURE);
			}
		}

		int result = m_operands.pop();

		if (!m_operands.is_empty())
		{
			std::cout << "Ne valja :(\n";
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

};

