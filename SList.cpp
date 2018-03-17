#include "data_structures.h"

SList::SList()
{
	head = NULL;
	tail = NULL;
	Llength = 0;
	Slength = 0;
	Capital = 0;
}

SList::~SList()
{
	Sentence * p = head;
	Sentence * q = head;
	while (Llength > 0)
	{
		q = q->next;
		delete p->data;
		delete p;
		p = q;
		Llength--;
	}
}

void SList::Add(String * s)
{
	Sentence * p = new Sentence;
	p->data = s;
	Slength = s->Slength;
	Capital = (*s)[0].data;
	if (!head)
	{
		head = p;
		tail = p;
		p->next = p;
		p->prev = p;
		Llength++;
		return;
	}
	tail->next = p;
	p->prev = tail;
	p->next = head;
	head->prev = p;
	tail = p;
	Llength++;
}

void SList::CopyAdd(String * s)
{
	Sentence * p = new Sentence;
	String * a = new String(*s);
	p->data = a;
	Slength = s->Slength;
	Capital = (*s)[0].data;
	if (!head)
	{
		head = p;
		tail = p;
		p->next = p;
		p->prev = p;
		Llength++;
		return;
	}
	tail->next = p;
	p->prev = tail;
	p->next = head;
	head->prev = p;
	tail = p;
	Llength++;
}

void SList::Remove(String & target)
{
	Sentence * p = Search(&target);
	if (!p)
		return;
	if (head == p && tail == p)
	{
		delete p;
		head = NULL;
		tail = NULL;
		return;
	}
	if (head == p)
		head = p->next;
	else if (tail == p)
		tail = p->prev;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	Llength -= 1;
}

Sentence * SList::Search(String * source, int start, int end)
{
	int length = end - start + 1;
	Sentence * p = head;
	if (!p)
		return NULL;
	do
	{
		if ((*p).data->Slength != length)
		{
			p = p->next;
			if (p == head)
				return NULL;
			continue;
		}
		int i;
		for (i = start; i <= end; i++)
		{
			if ((*source)[i].data != (*(*p).data)[i - start].data)
				break;
		}
		if (i > end)
		{
			return p;
		}
		p = p->next;
		if (p == head)
			return NULL;
	} while (1);
}

int SList::DicTraveler(BiTree * tree, int & i)
{
	Sentence * p = head;
	if (!p)
		return 0;
	int sum = 0;
	FileList fl;
	do
	{
		BiTNode * q = NULL;
		tree->SearchAVL(tree->root, p->data->WstringData()[0], q, NULL);
		Sentence * r = q->key->Search(p->data);
		if (!r)
		{
			p = p->next;
			continue;
		}
		Files * f = r->data->head;
		sum += fl.Search(f, i);
		p = p->next;
	} while (p != head);
	return sum;
}

Sentence * SList::Search(String * target)
{
	Sentence * p = head;
	if (!p)
		return NULL;
	do
	{
		if ((*p).data->Equal(*target))
			break;
		p = p->next;
		if (p == head)
			return NULL;
	} while (1);
	return p;
}

void SList::clear()
{
	Sentence * p = head;
	Sentence * q = head;
	while (Llength > 0)
	{
		q = q->next;
		delete p->data;
		delete p;
		p = q;
		Llength--;
	}
	head = NULL;
	tail = NULL;
	Llength = 0;
	Slength = 0;
	Capital = 0;
}
