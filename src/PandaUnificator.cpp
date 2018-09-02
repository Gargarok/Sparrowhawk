//============================================================================
// Name        : PandaUnificator.cpp
// Author      : PandaUnicity
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Windows.h>
#include "Tools/MemoryManager.hpp"

using namespace std;

int main() {
	MemoryManager* memManager = new MemoryManager();
	memManager -> readAll();

}
