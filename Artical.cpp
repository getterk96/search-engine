#include "Artical.h"

//build the artical from a String array
//Note: it will delete the wrong "," behind the author
Artical::Artical(String * r)
{
	title = r[0];
	question = r[1];
	author = r[2];
	if (author[author.Slength - 1].data == L'£¬')
	{
		author[author.Slength - 1].data = L'\0';
		--author.Slength;
	}
	content = r[3];
}
