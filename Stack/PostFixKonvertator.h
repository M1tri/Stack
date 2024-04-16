#pragma once

#include "Stack.h"
#include "String.h"

class PostFixKonvertator
{
private:
	Stack<char> m_stack;
	String m_input;
	String m_expresion;
	int index;

public:
	PostFixKonvertator(const String& expresion) : m_input(expresion), index(0) {}
	~PostFixKonvertator() {}

	void load_expresion(const String& expression)
	{
		index = 0;
		m_input = expression;
		m_expresion.clear();
	}

	void print_expresion()
	{
		m_expresion.print();
	}


	void convert()
	{
		while (peek() != '\0')
		{
			if (std::isdigit(peek()))
			{
				String buffer;
				buffer.push_back(consume());
				while (peek() != '\0' && std::isdigit(peek()))
				{
					buffer.push_back(consume());
				}

				m_expresion += buffer + ' ';
			}
			else if (peek() == '(' || peek() == '{' || peek() == '[')
			{
				m_stack.push(consume());
			}
			else if (peek() == ')' || peek() == '}' || peek() == ']')
			{
				while (!m_stack.is_empty() && m_stack.read_top() != '(' && m_stack.read_top() != '{' && m_stack.read_top() != '[')
				{
					m_expresion += m_stack.pop();
					m_expresion += ' ';
				}
				m_stack.pop();
				consume();
			}
			else if (mitri::is_operator(peek()))
			{
				if (!m_stack.is_empty())
				{
					if (mitri::is_operator(m_stack.read_top()))
					{
						if (mitri::cmp_operator(peek(), m_stack.read_top()))
						{
							m_stack.push(consume());
						}
						else
						{
							m_expresion += m_stack.pop();
							m_expresion += ' ';
							m_stack.push(consume());
						}
					}
					else
					{
						m_stack.push(consume());
					}
				}
				else
				{
					m_stack.push(consume());
				}
			}
			else if (peek() == ' ')
			{
				consume();
			}
			else
			{
				std::cerr << "Sjebo si nesto\n";
				exit(EXIT_FAILURE);
			}
		}

		if (!m_stack.is_empty())
		{
			while (!m_stack.is_empty())
			{
				m_expresion += m_stack.pop();
			}
		}
	}

	char peek()
	{
		if (index < m_input.length())
		{
			return m_input[index];
		}

		return '\0';
	}

	char consume()
	{
		return m_input[index++];
	}

	String& get_expresion()
	{
		return m_expresion;
	}

private:


};

