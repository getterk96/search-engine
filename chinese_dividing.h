#pragma once
#include "data_structures.h"

//Chinese words divider
class Divider
{
public:
	Divider();
	~Divider() {};

public:
	//a divider for Chinese dividing, returns the pointer of the tree
	BiTree * Divide(String & s, std::string path, int i);

private:
	//the max length of words in dic
	unsigned int m_wordlength = 0;
	SList * list;
	BiTree * tree;
};