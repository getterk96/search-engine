#include "data_structures.h"

BiTree::BiTree()
{
	root = NULL;
}

BiTree::~BiTree()
{
}

//建立左旋转函数
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
//建立右旋转函数
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
//调整AVLTree使之平衡
void BiTree::AdjustAVL(BiTNode * p)
{
	if (!p || !p->parent)
		return;
	//右单旋转
	if (p->parent->lsubr == 2 && p->lsubr == 1)
	{
		RightSpinAVL(p);
		p->lsubr = p->rchild->lsubr = 0;
	}
	//先左旋再右旋
	else if (p->parent->parent && p->parent->parent->lsubr == 2 && p->parent->lsubr == -1)
	{
		LeftSpinAVL(p);
		RightSpinAVL(p);
		p->lsubr = p->lchild->lsubr = 0;
		p->rchild->lsubr = 1;
	}
	//先右旋再左旋
	else if (p->parent->parent && p->parent->parent->lsubr == -2 && p->parent->lsubr == 1)
	{
		RightSpinAVL(p);
		LeftSpinAVL(p);
		p->lsubr = p->rchild->lsubr = 0;
		p->lchild->lsubr = 1;
	}
	//左单旋转
	else if (p->parent->lsubr == -2 && p->lsubr == -1)
	{
		LeftSpinAVL(p);
		p->lsubr = p->lchild->lsubr = 0;
	}
	AdjustAVL(p->parent);
}

//建立find函数，用于查找一个对象
bool BiTree::SearchAVL(BiTNode * r, wchar_t & key, BiTNode *& p, BiTNode * f)
{
	if (!r)
	{
		p = f;
		return false;
	}
	//比较是否是所查找的节点
	else if (key == r->key->Capital)
	{
		p = r;
		return true;
	}
	else if (key < r->key->Capital)
		//在左子树中继续查找
		return SearchAVL(r->lchild, key, p, r);
	else
		//在右子树中继续查找
		return SearchAVL(r->rchild, key, p, r);
}

//建立插入函数
void BiTree::InsertAVL(SList * n)
{
	BiTNode * p(NULL);
	BiTNode * q = new BiTNode;
	q->key = n;
	//先确定是否已经有相应节点
	if (!SearchAVL(root, q->key->Capital, p, NULL))
	{
		q->parent = p;
		//首节点
		if (!p)
		{
			root = q;
			return;
		}
		else if (q->key->Capital < p->key->Capital)
			p->lchild = q;   //插入 *s 为*p 的左孩子
		else if (q->key->Capital > p->key->Capital)
			p->rchild = q;   //插入 *s 为*p 的右孩子
	}
	BiTNode * traveler = q;
	//向上整理左子树高度减右子树高度
	while (traveler->parent)
	{
		traveler->parent->lchild == traveler ?
			++traveler->parent->lsubr :
			--traveler->parent->lsubr;
		//高度差整理为零时可停止整理
		if (!traveler->parent->lsubr)
			break;
		//高度差为2或者-2时停止整理，因为总可通过调整使高度差复原，所以不再向上继续整理
		if (traveler->parent->lsubr == 2 || traveler->parent->lsubr == -2)
			break;
		traveler = traveler->parent;
	}
	//调整二叉平衡树
	AdjustAVL(traveler);
}

//建立删除函数
void BiTree::DeleteAVL(BiTNode *root, wchar_t key)
{
	BiTNode * p(NULL);
	BiTNode * q(NULL);
	BiTNode * traveler(NULL);
	//先确定是否已经有相应节点
	if (SearchAVL(root, key, p, NULL))
	{
		q = p->lchild;
		if (!q)
		{
			traveler = p;
			//向上整理左子树高度减右子树高度
			while (traveler->parent)
			{
				traveler->parent->lchild == traveler ?
					--traveler->parent->lsubr :
					++traveler->parent->lsubr;
				//高度差整理为零时可停止整理
				if (!traveler->parent->lsubr)
					break;
				//高度差为2或者-2时停止整理，因为总可通过调整使高度差复原，所以不再向上继续整理
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
			//向上整理左子树高度减右子树高度
			while (traveler->parent)
			{
				traveler->parent->lchild == traveler ?
					--traveler->parent->lsubr :
					++traveler->parent->lsubr;
				//高度差整理为零时可停止整理
				if (!traveler->parent->lsubr)
					break;
				//高度差为2或者-2时停止整理，因为总可通过调整使高度差复原，所以不再向上继续整理
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
	//重新整理平衡树
	AdjustAVL(traveler);
}

//建立修改函数
void BiTree::EditAVL(BiTNode * r, wchar_t & key, SList * n)
{
	BiTNode * p;
	//查找
	SearchAVL(root, key, p, NULL);
	if (!p)
		return;
	p->key = n;
}
