#include "Search.h"
using namespace std;

ifstream *query;
wbuffer_convert<codecvt_utf8<wchar_t>> *convert;

Search::Search()
{

}

void Search::SearchUp(BiTree * tree, int total_pages)
{
	//����������
	query = new ifstream("query.txt");
	convert = new wbuffer_convert<codecvt_utf8<wchar_t>>(query->rdbuf());
	wistream wsource(convert);
	//��ʼ������ȡ�ؼ�������
	wchar_t temp_string[100];
	SList * list = new SList;
	while (wsource.getline(temp_string, 100, L'\n'))
	{
		int i = 0;
		String temp_wstring;
		while (1)
		{
			if (temp_string[i] == L' ' || temp_string[i] == L'\0')
			{
				//������ʼ��
				int pointer = 0;
				int temp_word_length = 16;
				//��ʼ�ִ�
				while (pointer < temp_wstring.Slength - 1)
				{
					//���½�β�Ĵ���
					if ((temp_wstring.Slength - pointer - 1) < temp_word_length)
						temp_word_length = temp_wstring.Slength - pointer;
					//�������ƥ��
					for (int i = 1; i <= temp_word_length - 1; i++)
					{
						wchar_t p = temp_wstring.Data()[pointer].data;
						BiTNode * q = NULL;
						//�����в�����Ӧ�Ľڵ�
						tree->SearchAVL(tree->root, p, q, NULL);
						if (q)
						{
							//�ڽڵ��в��Ҷ�Ӧ�Ĵ�
							Sentence * r = q->key->Search(&temp_wstring, pointer, pointer + i);
							if (r)
								list->CopyAdd(r->data);
						}
					}
					++pointer;
				}
				temp_wstring = L"";
				if (temp_string[i] == L'\0')
					break;
			}
			else
				temp_wstring.AddNode(temp_string[i]);
			++i;
		}
		//������������
		wofstream outfile("result.txt", ios::app);
		for (int i = 1; i <= total_pages; i++)
		{
			int sum = list->DicTraveler(tree, i);
			if (sum)
				outfile << '(' << i << ',' << sum << ") ";
		}
		outfile << endl;
		list->clear();
	}
}