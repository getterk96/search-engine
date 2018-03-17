#include "data_structures.h"
#include <fstream>
using namespace std;

String::String()
{
	data = new Word[2];  //
	size = 2;  //
	Slength = 0;
	head = NULL;
}

String::String(std::wstring & s)
{
	data = new Word[2];
	size = 2;
	Slength = 0;
	head = NULL;
	int index = 0;
	while (s[index] != '\0')  //
		AddNode(s[index++]);
}

String::String(wchar_t s[])
{
	data = new Word[2];
	size = 2;
	Slength = 0;
	int index = 0;
	head = NULL;
	while (s[index] != '\0')  //
		AddNode(s[index++]);
}

String::String(String & s)
{
	FileList f;
	head = f.copy(s.head);
	Slength = 0;
	data = new Word[2];
	size = 2;
	int index = 0;
	while (index < s.Slength)
		AddNode(s[index++].data);
	
}

String::~String()
{
	FileList f;
	delete data;
	f.clear(head);
}

void String::AddNode(wchar_t & w)
{
	if (size == Slength)
		Expand();
	data[Slength].data = w;
	++Slength;
}

void String::IndexOf(String & t,int & index)
{
	if (!Slength || !t.Slength)
		index = -1;
	for (int i = 0; i < t.Slength; i++)
	{
		int temp = -1;
		int p = 0;
		int q = i - 1;
		if (!i)
		{
			t[p].nextVal = temp;
			continue;
		}
		while (1)
		{
			if (p == i - 1 || t[p].data != t[q].data)
				break;
			temp++;
			++p;
			--q;
		}
		temp += 1;
		t[i].nextVal = temp;
	}
	//next_val优化
	for (int i = t.Slength - 1; i >= 0; i--)
	{
		int p = i;
		int q = t[p].nextVal;
		int temp = t[p].nextVal;
		while (1)
		{
			if (!p || t[p].data != t[q].data)
				break;
			temp = t[q].nextVal;
			if (temp == -1)
				break;
			p = q;
			q = t[q].nextVal;
		}
		t[p].nextVal = temp;
	}
	int i = index;
	if (index >= Slength)
	{
		index = -1;
		return;
	}
	//匹配部分
	int j = 0;
	int n = Slength;
	int m = t.Slength;
	while (i < n && j < m) 
	{
		if (j == -1 || data[i].data == t[j].data)
		{
			++i;
			++j;
		}
		else  j = t[j].nextVal;         // 模式串向右移动,
	}
	if (j == m)
		index = i - m;    // 匹配成功
	else
		index = -1;
	return;
}

String * String::SubString(int s, int e)   ///
{
	String * p = new String;
	for (int i = s; i <= e; i++)
		p->AddNode(data[i].data);
	return p;   //return之后的流程是什么？
}

void String::Concat(String & news)
{
	for (int i = 0; i < news.Slength; i++)
		AddNode(news[i].data);
	news.~String();
}

void String::Assign(String & s)
{
	delete data;
	Slength = 0;
	data = new Word[100];
	size = 100;
	for (int i = 0; i < s.Slength; i++)
		AddNode(s[i].data);
}

bool String::Equal(String & s)
{
	if (Slength != s.Slength)
		return false;
	for (int i = 0; i < Slength; i++)
	{
		if (data[i].data != s[i].data)
			return false;
	}
	return true;
}

Word & String::operator[](int i)
{
	return data[i];
}

String & String::operator=(String & a)
{
	//赋值
	if (this == &a)
		return *this;
	delete data;
	data = new Word[100];
	size = 100;
	Slength = 0;
	for (int i = 0; i < a.Slength; i++)
		if(a[i].data != L' ')
			AddNode(a[i].data);
	return *this;
}

String & String::operator=(wchar_t a[])
{
	//赋值
	delete data;
	data = new Word[2];
	size = 2;
	Slength = 0;
	for (int i = 0; i < wcslen(a); i++)
		if (a[i] != L' ')
			AddNode(a[i]);
	return *this;
	// TODO: 在此处插入 return 语句
}

void String::Display(wofstream * file)
{
	for (int i = 0; i < Slength; i++)
		if(data[i].data != L' ')
			(*file).put(data[i].data);
	*file << endl;
}

wstring String::WstringData()
{
	//将内容转为wstring输出
	wstring s = L"";
	for (int i = 0; i < Slength; i++)
		s += data[i].data;
	return s;
}

void String::Expand()
{
	//拓展空间
	Word * p = new Word[size * 2];
	for (int i = 0; i < Slength; i++)
		p[i] = data[i];
	delete data;
	data = p;
	size *= 2;
}

void String::DelSpace()
{
	//格式整理，删除空格及其他奇怪的操作符
	String * p = new String;
	Word * q = data;
	int new_length = Slength;
	for (int i = 0; i < Slength; i++)
	{
		if (q->data != L' ')
			p->AddNode(q->data);
		else
			--new_length;
	}
	delete data;
	data = p->Data();
	Slength = new_length;
}

Word * String::Data()
{
	return data;
}