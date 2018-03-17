#include "chinese_dividing.h"

using namespace std;

ifstream *source;
wbuffer_convert<codecvt_utf8<wchar_t>> *conv;

Divider::Divider()
{
	//切换输入流格式为utf-8
	source = new ifstream("词库.dic");
	conv = new wbuffer_convert<codecvt_utf8<wchar_t>>(source->rdbuf());
	wistream wsource(conv);
	//变量初始化
	tree = new BiTree;
	list = new SList[5900];
	wstring temp_string;
	m_wordlength = 16;
	int temp_first = 0;
	//建立字典，每个节点的结构为：首字符相同的所有词（一个SList）
	while (wsource >> temp_string)
	{
		String * temp_wstring = new String(temp_string);
		if (list[temp_first].Capital != (*temp_wstring)[0].data)
		{
			tree->InsertAVL(&list[temp_first]);
			++temp_first;
		}
		list[temp_first].Add(temp_wstring);  //
	}
	tree->InsertAVL(&list[temp_first]);
	delete source;
}

BiTree * Divider::Divide(String & s, string path, int index_of_page)
{
	//变量初始化
	FileList fl;
	int pointer = 0;
	int temp_word_length = m_wordlength;
	//开始分词
	while (pointer < s.Slength - 1)
	{
		//文章结尾的处理
		if ((s.Slength - pointer - 1) < temp_word_length)
			temp_word_length = s.Slength - pointer;
		//正向最大匹配
		for (int i = 1; i <= temp_word_length - 1; i++)
		{
			wchar_t p = s[pointer].data;
			BiTNode * q = NULL;
			//在树中查找相应的节点
			tree->SearchAVL(tree->root, p, q, NULL);
			if (q)
			{
				//在节点中查找对应的词
				Sentence * r = q->key->Search(&s, pointer, pointer + i);
				if (r)
				{
					//为词条r构建倒排文档
					fl.Add(r->data, index_of_page);
					pointer += i;
				}
			}
		}
		++pointer;
	}
	return tree;
}