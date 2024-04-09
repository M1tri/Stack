#pragma once

#include <iostream>
#include "Stack.h"
#include <string>

class PostFixRacunator
{
private:
	Stack<int> operands;
	Stack<char> operators;
	char* izraz;
	int index = 0;

public:
	PostFixRacunator(const char* izraz)
	{
		this->izraz = new char[len(izraz) + 1]();

		for (int i = 0; i < len(izraz); i++)
			this->izraz[i] = izraz[i];
	}
	~PostFixRacunator()
	{
		delete[] izraz;
	}

	int calculate_postfix()
	{
		int lenght = len(izraz);

		std::string buffer;

		while (peek() != '\0')
		{
			if (std::isdigit(peek()))
			{
				buffer.push_back(consume());

				while (peek() != '\0' && std::isdigit(peek()))
				{
					buffer.push_back(consume());
				}

				int n = std::stoi(buffer);
				operands.push(n);
				buffer.clear();
			}
			else if (peek() == ' ')
			{
				consume();
			}
			else if (peek() == '+')
			{
				int op2;
				int op1;
				try
				{
					op2 = operands.pop();
					op1 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 + op2;
				operands.push(rez);
				consume();
			}
			else if (peek() == '-')
			{
				int op2;
				int op1;
				try
				{
					op2 = operands.pop();
					op1 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 - op2;

				operands.push(rez);
				consume();
			}
			else if (peek() == '*')
			{
				int op2;
				int op1;
				try
				{
					op2 = operands.pop();
					op1 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 * op2;

				operands.push(rez);
				consume();
			}
			else if (peek() == '/')
			{
				int op2;
				int op1;
				try
				{
					op2 = operands.pop();
					op1 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 / op2;

				operands.push(rez);
				consume();
			}
			else
			{
				std::cerr << "Nesto si prijatelju zajebo\n";
				exit(EXIT_FAILURE);
			}
		}

		int result = operands.pop();

		if (!operands.is_empty())
		{
			std::cout << "Ne valja :(\n";
		}

		return result;
	}

	char peek() const
	{
		if (index > len(izraz))
			return '\0';

		return izraz[index];
	}

	char consume()
	{
		return izraz[index++];
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

