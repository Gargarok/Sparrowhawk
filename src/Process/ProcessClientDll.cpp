/*
 * ProcessClientDll.cpp
 *
 *  Created on: 2 sept. 2018
 *      Author: Nous
 */

#include <ProcessClientDll.hpp>

void processClientModule(MemoryManager* memManager, MODULEENTRY32* clientModule) {
   // Get module base address
   DWORD dwClientBase = reinterpret_cast<DWORD>(clientModule -> modBaseAddr);

   DWORD dwRadarBase = 0;
   DWORD& dwRadarBaseAddress = dwRadarBase;
   memManager -> readMem(dwClientBase + 0x5071E6C, dwRadarBase);
}

