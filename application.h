#pragma once
#include "find_data.h"
#include "chinese_dividing.h"
#include "Search.h"
#include <iostream>
#include <io.h>
#include <string>

using namespace std;

void dir(string path);

class Application
{
public:
	Application() {}
	~Application() {}

public:
	void run();
};