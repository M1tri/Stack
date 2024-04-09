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

	int calculate_postfix()
	{
		int lenght = len(izraz);

		std::string buffer;

		while (peak() != '\0')
		{
			if (std::isdigit(peak()))
			{
				buffer.push_back(consume());

				while (peak() != '\0' && std::isdigit(peak()))
				{
					buffer.push_back(consume());
				}

				int n = std::stoi(buffer);
				operands.push(n);
				buffer.clear();
			}
			else if (peak() == ' ')
			{
				consume();
			}
			else if (peak() == '+')
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
			else if (peak() == '-')
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
			else if (peak() == '*')
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
			else if (peak() == '/')
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

	// prepares operands and operators
	void prepare_prefix()
	{
		int lenght = len(izraz);

		while (peak() != '\0' && !std::isdigit(peak()))
		{
			if (peak() == '/' || peak() == '*' || peak() == '+' || peak() == '-')
			{
				operators.push(consume());
			}
			else if (peak() == ' ')
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
		while (peak() != '\0')
		{
			if (std::isdigit(peak()))
			{
				std::string buffer;
				buffer.push_back(consume());

				while (std::isdigit(peak()))
				{
					buffer.push_back(consume());
				}
				int n = std::stoi(buffer);
				pom.push(n);
			}
			else if (peak() == ' ')
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

	int calculate_prefix()
	{
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
	char peak() const
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

