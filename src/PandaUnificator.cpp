//============================================================================
// Name        : PandaUnificator.cpp
// Author      : PandaUnicity
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ProcessClientDll.hpp>
#include <MemoryManager.hpp>

using namespace std;

int main() {
   MemoryManager* memManager = new MemoryManager();

   // debug
   //memManager -> readAll();

   std::cout << "Looking for process..." << std::endl;

   if (memManager->attach("csgo.exe")) {
      std::cout << "Pocess found !" << std::endl;
      if (memManager->grabModule("client_panorama.dll")) {
         std::cout << "Module found within CS GO !" << std::endl;
         for (ModuleWrapper modWrapper : memManager->getModules()) {
            MODULEENTRY32* clientModule = modWrapper.getModule();
            processClientModule(memManager, clientModule);

         }
      }
      else {
         std::cout << "Module not found. Exiting" << std::endl;
      }
   }
   else {
      std::cout << "CS:GO process not found. Exiting" << std::endl;
   }

}
