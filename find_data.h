#pragma once
#include "data_structures.h"
#include "Artical.h"

//to find the key informations of the html
class Finder
{
public:
	Finder();
	~Finder();
public:
	Artical * Finder::Find(std::string path);
};