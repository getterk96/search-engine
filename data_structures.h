#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <locale>
#include <codecvt>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define MAXSIZE 20

struct BiTNode;
class SList;

struct Word
{
	int nextVal = 0;
	wchar_t data = ' ';  ///
};

//class of file list
struct Files
{
	short freq_of_occur = 0;
	short file = 0;
	Files * next = NULL;
	Files * prev = NULL;
};

class String
{
public:
	String();
	String(std::wstring & s);
	String(wchar_t s[]);
	String(String & s);
	~String();

public:
	void AddNode(wchar_t & w);
	void String::IndexOf(String & t, int & index); //求出所找的子串的位置，如果未找到或发生异常即返回-1
	String * SubString(int s, int e);
	void Concat(String & news);
	void Assign(String & s);
	bool Equal(String & s);
	Word & operator [](int i); //如果index越界则返回-1，否则返回正常的位置
	String & operator =(String & a);
	String & operator =(wchar_t a[]);
	void Display(std::wofstream * file);
	std::wstring WstringData();
	void Expand();
	void DelSpace();
	Word * Data();

public:
	int Slength;
	Files * head;

private:
	int size;
	Word * data;
};

//the class of AVL tree
class BiTree
{
public:
	BiTree();
	~BiTree();

public:
	void InsertAVL(SList * n);
	void DeleteAVL(BiTNode * root, wchar_t key);
	void EditAVL(BiTNode * r, wchar_t & key, SList * n);
	void AdjustAVL(BiTNode * p);
	bool SearchAVL(BiTNode * r, wchar_t & key, BiTNode *& p, BiTNode * f);
	void LeftSpinAVL(BiTNode * p);
	void RightSpinAVL(BiTNode * p);

public:
	BiTNode * root;
};

class Stack
{
public:
	Stack();
	~Stack();

public:
	int Push(String * newItem);
	String * Pop();
	String ** Top();
	int Expand();
	bool Empty();
	void reset();

private:
	int size;
	String ** top;
	String ** base;
};

struct Sentence
{
	String * data;
	Sentence * next = NULL;
	Sentence * prev = NULL;
};

class SList
{
public:
	SList();
	~SList();

public:
	void Add(String * s);
	void CopyAdd(String * s);
	void Remove(String & target);
	Sentence * Search(String * source, int start, int end);
	int DicTraveler(BiTree * tree, int & i);
	Sentence * Search(String * target);
	void clear();

public:
	int Llength;
	int Slength;
	wchar_t Capital = 0;

private:
	Sentence * head;
	Sentence * tail;
};

//the class of file list
class FileList
{
public:
	FileList() {}
	~FileList() {}
public:
	void Add(String * r, int & i);
	int Search(Files * head, int & i);
	void Edit(Files * head, int & i, int new_occ);
	void Del(Files * head, int & i);
	void clear(Files * head);
	Files * copy(Files * head);
};

struct BiTNode
{
	SList * key = NULL;
	BiTNode * lchild = NULL;
	BiTNode * rchild = NULL;
	BiTNode * parent = NULL;
	int lsubr = 0;
};