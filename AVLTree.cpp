#include "data_structures.h"

BiTree::BiTree()
{
	root = NULL;
}

BiTree::~BiTree()
{
}

//��������ת����
void BiTree::LeftSpinAVL(BiTNode * p)
{
	p->parent->rchild = p->lchild;
	if (p->lchild)
		p->lchild->parent = p->parent;
	p->lchild = p->parent;
	if (!p->parent->parent)
	{
		root = p;
		p->parent = NULL;
	}
	else
	{
		p->parent->parent->rchild == p->parent ?
			p->parent->parent->rchild = p :
			p->parent->parent->lchild = p;
		p->parent = p->parent->parent;
	}
	p->lchild->parent = p;
}
//��������ת����
void BiTree::RightSpinAVL(BiTNode * p)
{
	p->parent->lchild = p->rchild;
	if (p->rchild)
		p->rchild->parent = p->parent;
	p->rchild = p->parent;
	if (!p->parent->parent)
	{
		root = p;
		p->parent = NULL;
	}
	else
	{
		p->parent->parent->rchild == p->parent ?
			p->parent->parent->rchild = p :
			p->parent->parent->lchild = p;
		p->parent = p->parent->parent;
	}
	p->rchild->parent = p;
}
//����AVLTreeʹ֮ƽ��
void BiTree::AdjustAVL(BiTNode * p)
{
	if (!p || !p->parent)
		return;
	//�ҵ���ת
	if (p->parent->lsubr == 2 && p->lsubr == 1)
	{
		RightSpinAVL(p);
		p->lsubr = p->rchild->lsubr = 0;
	}
	//������������
	else if (p->parent->parent && p->parent->parent->lsubr == 2 && p->parent->lsubr == -1)
	{
		LeftSpinAVL(p);
		RightSpinAVL(p);
		p->lsubr = p->lchild->lsubr = 0;
		p->rchild->lsubr = 1;
	}
	//������������
	else if (p->parent->parent && p->parent->parent->lsubr == -2 && p->parent->lsubr == 1)
	{
		RightSpinAVL(p);
		LeftSpinAVL(p);
		p->lsubr = p->rchild->lsubr = 0;
		p->lchild->lsubr = 1;
	}
	//����ת
	else if (p->parent->lsubr == -2 && p->lsubr == -1)
	{
		LeftSpinAVL(p);
		p->lsubr = p->lchild->lsubr = 0;
	}
	AdjustAVL(p->parent);
}

//����find���������ڲ���һ������
bool BiTree::SearchAVL(BiTNode * r, wchar_t & key, BiTNode *& p, BiTNode * f)
{
	if (!r)
	{
		p = f;
		return false;
	}
	//�Ƚ��Ƿ��������ҵĽڵ�
	else if (key == r->key->Capital)
	{
		p = r;
		return true;
	}
	else if (key < r->key->Capital)
		//���������м�������
		return SearchAVL(r->lchild, key, p, r);
	else
		//���������м�������
		return SearchAVL(r->rchild, key, p, r);
}

//�������뺯��
void BiTree::InsertAVL(SList * n)
{
	BiTNode * p(NULL);
	BiTNode * q = new BiTNode;
	q->key = n;
	//��ȷ���Ƿ��Ѿ�����Ӧ�ڵ�
	if (!SearchAVL(root, q->key->Capital, p, NULL))
	{
		q->parent = p;
		//�׽ڵ�
		if (!p)
		{
			root = q;
			return;
		}
		else if (q->key->Capital < p->key->Capital)
			p->lchild = q;   //���� *s Ϊ*p ������
		else if (q->key->Capital > p->key->Capital)
			p->rchild = q;   //���� *s Ϊ*p ���Һ���
	}
	BiTNode * traveler = q;
	//���������������߶ȼ��������߶�
	while (traveler->parent)
	{
		traveler->parent->lchild == traveler ?
			++traveler->parent->lsubr :
			--traveler->parent->lsubr;
		//�߶Ȳ�����Ϊ��ʱ��ֹͣ����
		if (!traveler->parent->lsubr)
			break;
		//�߶Ȳ�Ϊ2����-2ʱֹͣ������Ϊ�ܿ�ͨ������ʹ�߶Ȳԭ�����Բ������ϼ�������
		if (traveler->parent->lsubr == 2 || traveler->parent->lsubr == -2)
			break;
		traveler = traveler->parent;
	}
	//��������ƽ����
	AdjustAVL(traveler);
}

//����ɾ������
void BiTree::DeleteAVL(BiTNode *root, wchar_t key)
{
	BiTNode * p(NULL);
	BiTNode * q(NULL);
	BiTNode * traveler(NULL);
	//��ȷ���Ƿ��Ѿ�����Ӧ�ڵ�
	if (SearchAVL(root, key, p, NULL))
	{
		q = p->lchild;
		if (!q)
		{
			traveler = p;
			//���������������߶ȼ��������߶�
			while (traveler->parent)
			{
				traveler->parent->lchild == traveler ?
					--traveler->parent->lsubr :
					++traveler->parent->lsubr;
				//�߶Ȳ�����Ϊ��ʱ��ֹͣ����
				if (!traveler->parent->lsubr)
					break;
				//�߶Ȳ�Ϊ2����-2ʱֹͣ������Ϊ�ܿ�ͨ������ʹ�߶Ȳԭ�����Բ������ϼ�������
				if (traveler->parent->lsubr == 2 || traveler->parent->lsubr == -2)
					break;
				traveler = traveler->parent;
			}
			p->parent->lchild = p ?
				p->parent->lchild = p->rchild :
				p->parent->rchild = p->lchild;
			p->rchild->parent = p->parent;
			delete p;
		}
		else
		{
			while (q->rchild)
				q = q->rchild;
			traveler = q;
			//���������������߶ȼ��������߶�
			while (traveler->parent)
			{
				traveler->parent->lchild == traveler ?
					--traveler->parent->lsubr :
					++traveler->parent->lsubr;
				//�߶Ȳ�����Ϊ��ʱ��ֹͣ����
				if (!traveler->parent->lsubr)
					break;
				//�߶Ȳ�Ϊ2����-2ʱֹͣ������Ϊ�ܿ�ͨ������ʹ�߶Ȳԭ�����Բ������ϼ�������
				if (traveler->parent->lsubr == 2 || traveler->parent->lsubr == -2)
					break;
				traveler = traveler->parent;
			}
			p->key = q->key;
			q->parent->lchild = q ?
				q->parent->lchild = q->lchild :
				q->parent->rchild = q->lchild;
			q->lchild->parent = q->parent;
			delete q;
		}
	}
	//��������ƽ����
	AdjustAVL(traveler);
}

//�����޸ĺ���
void BiTree::EditAVL(BiTNode * r, wchar_t & key, SList * n)
{
	BiTNode * p;
	//����
	SearchAVL(root, key, p, NULL);
	if (!p)
		return;
	p->key = n;
}
