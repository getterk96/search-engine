#pragma once
#include "data_structures.h"

class Artical              //ÎÄµµÀà
{
public:
	Artical(String * r);
	~Artical() {}

public:
	//title
	String title;
	//question
	String question;
	//author
	String author;
	//content
	String content;
};
