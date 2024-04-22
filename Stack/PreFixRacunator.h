#pragma once

#include <iostream>
#include "Stack.h"
#include <string>
#include "String.h"

// Ovo msm da ne radi uvek ali previse me mrzi da ga doradjujem retko se pada
class PreFixRacunator
{
private:
	Stack<double> m_operands;
	Stack<char> m_operators;
	String m_izraz;
	int m_index = 0;

public:
	PreFixRacunator(const char* izraz) : m_izraz(izraz) 
	{
		m_index = m_izraz.length() - 1;
	
	}
	~PreFixRacunator() {}

	int calculate_prefix()
	{
		while (peek() != '\0')
		{
			if (std::isdigit(peek()))
			{
				String m_buffer;

				m_buffer.push_back(consume());
				while (peek() != '\0' && std::isdigit(peek()))
				{
					m_buffer.push_back(consume());
				}
				double n = mitri::Stoi(m_buffer);
				m_operands.push(n);
			}
			else if (peek() == '+')
			{
				consume();
				double op1 = m_operands.pop();
				double op2 = m_operands.pop();

				double rez = op1 + op2;
				m_operands.push(rez);
			}
			else if (peek() == '-')
			{
				consume();
				double op1 = m_operands.pop();
				double op2 = m_operands.pop();

				double rez = op1 - op2;
				m_operands.push(rez);
			}
			else if (peek() == '*')
			{
				consume();
				double op1 = m_operands.pop();
				double op2 = m_operands.pop();

				double rez = op1 * op2;
				m_operands.push(rez);
			}
			else if (peek() == '/')
			{
				consume();
				double op1 = m_operands.pop();
				double op2 = m_operands.pop();

				double rez = op1 / op2;
				m_operands.push(rez);
			}
			else if (peek() == ' ')
			{
				consume();
			}
			else
			{
				exit(EXIT_FAILURE);
			}
		}

		int rez = m_operands.pop();

		if (!m_operands.is_empty())
			exit(EXIT_FAILURE);

		return rez;
	}

	char peek() const
	{
		if (m_index < 0)
			return '\0';

		return m_izraz[m_index];
	}

	char consume()
	{
		return m_izraz[m_index--];
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

