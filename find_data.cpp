#include "find_data.h"
#include <fstream>
using namespace std;

ifstream *wsource;
wbuffer_convert<codecvt_utf8<wchar_t>> *aconv;

Finder::Finder()
{
}

Finder::~Finder()
{
}

Artical * Finder::Find(std::string path)
{
	//加载html
	wsource = new ifstream(path);
	aconv = new wbuffer_convert<codecvt_utf8<wchar_t>>(wsource->rdbuf());
	wistream resource(aconv);
	//变量初始化
	String source;
	wchar_t input;
	resource.get(input);
	//读入文档
	while (resource.get(input))
		source.AddNode(input);

	Stack tag_stack;
	Stack type_stack;
	//记录“<”的位置
	int index_ls = 0;
	//记录“</”的位置
	int index_le = 0;
	//记录“/>”的位置
	int index_rse = 0;
	//记录“>”的位置
	int index_re = 0;
	//记录“ ”的位置
	int index_mi = 0;
	//确定找到的是结果的哪个部分
	int index_target = 0;
	//确定选取的起点
	int last_point = 0;

	//比对样本
	String tag_target[4] = {L"title", L"h2", L"span", L"div"};
	String type_target[4] = {L"", L"class=\"question-title\"", L"class=\"author\"",  L"class=\"content\""};
	String * result = new String[4];
	String l_start(L"<");
	String l_end(L"</");
	String r_selfend(L"/>");
	String r_end(L">");
	String m_inter(L" ");
	//临时标签和类型
	String * tag = new String(L"");
	String * type = new String(L"");

	while (1)
	{
		//比较“<”和“<\”谁先出现
		source.IndexOf(l_start, index_ls);
		source.IndexOf(l_end, index_le);
		//检查自封闭标签
		if(index_rse != -1)
			source.IndexOf(r_selfend, index_rse);
		index_re = index_ls;
		source.IndexOf(r_end, index_re);
		//自封闭标签的处理
		if (index_rse < index_le && index_rse != -1 && index_re > index_rse)
		{
			index_le = index_rse + 1;
			index_rse = index_ls = index_le;
			continue;
		}
		//如果“<”在“</”
		if (index_ls < index_le)
		{
			index_mi = index_ls;
			index_re = index_ls;
			source.IndexOf(m_inter, index_mi);
			source.IndexOf(r_end, index_re);
			if (index_mi < index_re)
			{
				tag = source.SubString(index_ls + 1, index_mi - 1);
				type = source.SubString(index_mi + 1, index_re - 1);
			}
			else
				tag = source.SubString(index_ls + 1, index_re - 1);
			index_ls = index_re;
			tag_stack.Push(tag);
			tag = new String(L"");
			type_stack.Push(type);
			type = new String(L"");
			for (int m = 0; m < 4; m++)
				if ((*tag_stack.Top())->Equal(tag_target[m]) && (*type_stack.Top())->Equal(type_target[m]))
					last_point = ++index_re;
			index_le = index_ls;
		}
		//另外一种情况
		else
		{
			for(int m = 0; m < 4; m++)
				//找到匹配项
				if ((*tag_stack.Top())->Equal(tag_target[m]) && (*type_stack.Top())->Equal(type_target[m]))
				{
					index_ls = index_le;
					source.IndexOf(type_target[3], index_ls);
					//提取但不提取最后一个文章的content
					if (m != 3 || index_ls != -1)
					{
						if (source[last_point].data == L'\n') ++last_point;
						while (last_point != index_le)
						{
							result[m].AddNode(source[last_point].data);
							++last_point;
						}
						last_point = 0;
					}
					else
					{
						while (!tag_stack.Empty())
							delete tag_stack.Pop();
						while (!type_stack.Empty())
							delete type_stack.Pop();
						index_target = 1;
					}
				}
			//提取栈顶标签
			if (index_target == 1)
				break;
			index_mi = index_le;
			index_re = index_le;
			source.IndexOf(m_inter, index_mi);
			source.IndexOf(r_end, index_re);
			index_le += 2;
			while (index_le != index_mi && index_le != index_re)
			{
				tag->AddNode(source[index_le].data);
				++index_le;
			}
			//一直pop到匹配为止
			while (!(*(tag_stack.Top()))->Equal(*(tag)))
			{
				delete tag_stack.Pop();
				delete type_stack.Pop();
			}
			delete tag_stack.Pop();
			delete type_stack.Pop();
			delete tag;
			tag = new String(L"");
			index_ls = index_le;
		}
	}
	//清空操作
	while(!tag_stack.Empty())
		delete tag_stack.Pop();
	while (!type_stack.Empty())
		delete type_stack.Pop();
	delete tag;
	delete type;
	delete aconv;
	delete wsource;
	//格式处理操作
	int finder = 0;
	for (int i = 0; i < 4; i++)
	{
		while (1)
		{
			result[i].IndexOf((String)L"<", finder);
			if (finder == -1)
				break;
			for(int j = 0;;j++)
			{
				if (result[i][finder + j].data == L'>')
				{
					result[i][finder + j].data = L' ';
					break;
				}
				result[i][finder + j].data = L' ';
			}
		}
		//result[i].Display(&info);
	}
	//info.close();
	//for (int i = 0; i < 4; i++)
		//result[i].DelSpace();
	/*String content;
	for (int i = 0; i < result[3].Slength; i++)
		if (result[3][i].data != L' ' && result[3][i].data != L'\n')
			content.AddNode(result[3][i].data);*/

	Artical * r = new Artical(result);
	return r;
}