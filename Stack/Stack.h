#pragma once
#include <iostream>
template <typename T>

class Stack
{
private:
	int size;
	int top;
	T* data;

public:
	Stack(int size = 10) :size(size), top(-1)
	{
		data = new T[size]();
	}

	~Stack()
	{
		delete[] data;
	}

	bool push(T element)
	{
		if (top == size - 1)
		{
			resize(2 * size);
		}

		data[++top] = element;
		return true;
	}
	T pop()
	{
		if (top == -1)
			throw "Prazan stek\n";

		return data[top--];
	}

	T read_top()
	{
		if (top == -1)
			throw "Prazan stek\n";

		return data[top];
	}

	bool is_empty()
	{
		return top == -1;
	}

	bool is_full()
	{
		return top == (size - 1);
	}

	int curr_size()
	{
		return top + 1;
	}

private:

	void resize(int new_size)
	{
		T* pom = new T[new_size]();

		int limit = top + 1;

		if (new_size < top)
		{
			limit = new_size;
		}

		for (int i = 0; i < limit; i++)
		{
			pom[i] = data[i];
		}

		delete[] data;

		data = new T[new_size]();

		for (int i = 0; i < limit; i++)
		{
			data[i] = pom[i];
		}

		size = new_size;
		delete[] pom;
	}


};

