#include "application.h"
using namespace std;

void Application::run()
{
	dir("input");
	cout << "´¦ÀíÍê±Ï£¬";
}

void dir(string path)
{
	Finder finder;
	Divider divider;
	intptr_t hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;

	//find out all the htmls under the category of "input"
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").append(".html").c_str(), &fileInfo)) == -1) {
		return;
	}

	BiTree * tree;
	Search search;
	int index_of_web = 0;
	do {
		string s(fileInfo.name);
		if (s[0] >= '0' && s[0] <= '9')
		{
			string p = "input\\" + s;
			//get the target information artical
			Artical * t = finder.Find(p);
			++index_of_web;
			//divide the artical and establish the filelist
			tree = divider.Divide(t->title, p, index_of_web);
			tree = divider.Divide(t->author, p, index_of_web);
			tree = divider.Divide(t->question, p, index_of_web);
			tree = divider.Divide(t->content, p, index_of_web);
		}
	} while (_findnext(hFile, &fileInfo) == 0);

	//read the query.txt and search all the key words in the filelist
	search.SearchUp(tree, index_of_web);

	//close the file
	_findclose(hFile);
	return;
}