//============================================================================
// Name        : PandaUnificator.cpp
// Author      : PandaUnicity
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Windows.h>
#include "Tools/HandleTools.hpp"

using namespace std;

int main() {
	cout << "Balec" << endl; // prints Balec
	HANDLE mumbleHandle = openHandle("mumble.exe");
	cout << "HANDLE: " << mumbleHandle << endl;
	return 0;
}
