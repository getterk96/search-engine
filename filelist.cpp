#include "data_structures.h"

void FileList::Add(String * r, int & i)
{
	Files * f = r->head;
	//���������
	if (!f)
	{
		Files * nf = NULL;
		while(!nf)
			nf = new Files;
		nf->file = i;
		++nf->freq_of_occur;
		r->head = nf;
	}
	else
	{
		//�ҵ��ĵ������β
		while (f->next)
		{
			if (f->file == i)
			{
				f->freq_of_occur++;
				break;
			}
			f = f->next;
		}
		if (!f->next)
		{
			if (f->file == i)
			{
				//û���ҵ��½ڵ�Ĳ���
				f->freq_of_occur++;
			}
			else
			{
				//�����½ڵ��һϵ�в���
				Files * nf = NULL;
				while (!nf)
					nf = new Files;
				nf->file = i;
				++nf->freq_of_occur;
				f->next = nf;
				nf->prev = f;
				return;
			}
		}
		while (f->prev && f->freq_of_occur > f->prev->freq_of_occur)
		{
			short temp = f->file;
			f->file = f->prev->file;
			f->prev->file = temp;
			temp = f->freq_of_occur;
			f->freq_of_occur = f->prev->freq_of_occur;
			f->prev->freq_of_occur = temp;
			f = f->prev;
		}
	}
}

int FileList::Search(Files * head, int & i)
{
	Files * p = head;
	if (!p)
		return 0;
	while (p)
	{
		if (p->file == i)
			return p->freq_of_occur;
		p = p->next;
	}
	return 0;
}

void FileList::Edit(Files * head, int & i, int new_occ)
{
	Files * p = head;
	if (!p)
		return;
	while (p)
	{
		if (p->file == i)
			break;
		p = p->next;
	}
	p->freq_of_occur = new_occ;
}

void FileList::Del(Files * head, int & i)
{
	//ɾ������
	Files * p = head;
	Files * q = NULL;
	if (!p)
		return;
	while (p)
	{
		if (p->file == i)
			break;
		q = p;
		p = p->next;
	}
	q->next = p->next;
	p->next->prev = q;
	delete p;
}

void FileList::clear(Files * head)
{
	Files * p = head;
	Files * q = head;
	while (q)
	{
		q = q->next;
		delete p;
		p = q;
	}
}

Files * FileList::copy(Files * head)
{
	Files * new_head = NULL;
	Files * p = head;
	Files * q = NULL;
	if (q)
		while (q->next)
			q = q->next;
	while (p)
	{
		if (!new_head)
		{
			new_head = new Files;
			new_head->file = p->file;
			new_head->freq_of_occur = p->freq_of_occur;
			q = new_head;
		}
		else
		{
			q->next = new Files;
			q->next->prev = q;
			q->next->file = p->file;
			q->next->freq_of_occur = p->freq_of_occur;
			q = q->next;
		}
		p = p->next;
	}
	return new_head;
}
