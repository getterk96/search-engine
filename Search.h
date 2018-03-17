#pragma once
#include "data_structures.h"

//the class aimed at searching the filelist to find out the result
class Search
{
public:
	Search();
	~Search() {};

public:
	void SearchUp(BiTree * tree, int total_pages);
};