#include "data_structures.h"

Stack::Stack()
{
	base = new String *[100];
	size = 100;
	top = base;
}

Stack::~Stack()
{
	delete base;
}

int Stack::Push(String * newItem)
{
	if (top - base >= size)
		if(Expand())
			return 1;
	*top++ = newItem;
	return 0;
}

String * Stack::Pop()
{
	if (top == base)
		return NULL;
	return *--top;
}

String ** Stack::Top()
{
	if (top == base)
		return NULL;
	String ** p = top;
	return --p;
}

int Stack::Expand()
{
	String ** p = new String *[size + 100];
	String ** q = base;
	for (int i = 0; i < size; i++)
	{
		p[i] = *q;
		++q;
	}
	base = p;
	top = (p += size);
	size += 100;
	delete q;
	return 0;
}

bool Stack::Empty()
{
	if (top == base)
		return true;
	return false;
}

void Stack::reset()
{
	top = base;
}
