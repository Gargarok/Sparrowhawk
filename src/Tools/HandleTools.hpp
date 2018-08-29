/*
 * HandleTools.hpp
 *
 *  Created on: 28 août 2018
 *      Author: Nous
 */

#ifndef TOOLS_HANDLETOOLS_HPP_
#define TOOLS_HANDLETOOLS_HPP_

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

HANDLE openHandle(const std::string& ProcessName);

#endif /* TOOLS_HANDLETOOLS_HPP_ */
