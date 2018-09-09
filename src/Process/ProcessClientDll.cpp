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
   std::cout << "CLIENT BASE VALUE: " << dwClientBase << std::endl;

   //DWORD dwRadarBase = 0;
   //memManager -> readMem(dwClientBase + RADAR_BASE_OFFSET, dwRadarBase);
   //std::cout << "DWRADARBASE VALUE: " << dwRadarBase << std::endl;

   DWORD dwLocalPlayer = 0;
   memManager -> readMem<DWORD>(dwClientBase + LOCAL_PLAYER_OFFSET, dwLocalPlayer);
   std::cout << "LOCAL PLAYER VALUE: " << dwLocalPlayer << std::endl;
}

