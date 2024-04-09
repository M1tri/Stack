#pragma once

#include <iostream>
#include "Stack.h"
#include <string>

class PreFixRacunator
{
private:
	Stack<int> operands;
	Stack<char> operators;
	char* izraz;
	int index = 0;

public:
	PreFixRacunator(const char* izraz)
	{
		this->izraz = new char[len(izraz) + 1]();

		for (int i = 0; i < len(izraz); i++)
			this->izraz[i] = izraz[i];
	}
	~PreFixRacunator()
	{
		delete[] izraz;
	}

	// prepares operands and operators

	int calculate_prefix()
	{
		prepare_prefix();

		if (operands.is_empty() || operators.is_empty())
		{
			std::cout << "Zovi prepare_prefix majmune\n";
			return 0;
		}

		while (!operators.is_empty())
		{
			char op = operators.pop();

			if (op == '+')
			{
				int op2;
				int op1;

				try
				{
					op1 = operands.pop();
					op2 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 + op2;
				operands.push(rez);
			}
			else if (op == '-')
			{
				int op2;
				int op1;
				try
				{
					op1 = operands.pop();
					op2 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 - op2;
				operands.push(rez);
			}
			else if (op == '*')
			{
				int op2;
				int op1;
				try
				{
					op1 = operands.pop();
					op2 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 * op2;
				operands.push(rez);
			}
			else if (op == '/')
			{
				int op2;
				int op1;
				try
				{
					op1 = operands.pop();
					op2 = operands.pop();
				}
				catch (...)
				{
					std::cout << "Mising operands\n";
					return 0;
				}

				int rez = op1 / op2;
				operands.push(rez);
			}
		}


		int result = operands.pop();

		if (!operands.is_empty())
		{
			std::cout << "Sjebo si se :(\n";
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
	void prepare_prefix()
	{
		int lenght = len(izraz);

		while (peek() != '\0' && !std::isdigit(peek()))
		{
			if (peek() == '/' || peek() == '*' || peek() == '+' || peek() == '-')
			{
				operators.push(consume());
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
				std::string buffer;
				buffer.push_back(consume());

				while (std::isdigit(peek()))
				{
					buffer.push_back(consume());
				}
				int n = std::stoi(buffer);
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
			operands.push(pom.pop());
		}

	}
};

