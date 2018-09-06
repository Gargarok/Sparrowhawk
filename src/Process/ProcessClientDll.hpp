/*
 * ProcessClientDll.hpp
 *
 *  Created on: 2 sept. 2018
 *      Author: Nous
 */

#ifndef PROCESS_PROCESSCLIENTDLL_HPP_
#define PROCESS_PROCESSCLIENTDLL_HPP_

#include <Windows.h>
#include <tlhelp32.h>
#include <MemoryManager.hpp>

#define RADAR_BASE_OFFSET 0x5071E6C

void processClientModule(MemoryManager* memManager, MODULEENTRY32* clientModule);

#endif /* PROCESS_PROCESSCLIENTDLL_HPP_ */
