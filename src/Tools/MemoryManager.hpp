/*
 * MemoryManager.hpp
 *
 *  Created on: 30 août 2018
 *      Author: Nous
 */

#ifndef TOOLS_MEMORYMANAGER_HPP_
#define TOOLS_MEMORYMANAGER_HPP_

#include <iostream>
#include <set>
#include <Windows.h>
#include <tlhelp32.h>

class ModuleWrapper {
private :
	MODULEENTRY32* module;
public:
	ModuleWrapper(MODULEENTRY32* module);
	MODULEENTRY32* getModule();
	bool operator<(const ModuleWrapper& comp) const;
};

class MemoryManager {
private:
	// Private members: We are going to setup some getters later on!
	HANDLE m_hProcess; // The HANDLE to the process to attach
	DWORD m_dwProcessId; // The Process Id of the process to attach
	std::set<ModuleWrapper> m_Modules; // std::vector containing all the modules we grab from the process

public:
	MemoryManager();
	//MemoryManager(const std::string& strProcessName);

	// Attach to a process based on strProcessName
	// Returns true on success, false on failure
	bool Attach(const std::string& strProcessName);

	// Grabs a module and adds it to m_Modules if found based on strModuleName
	// Returns true on success, false on failure
	bool GrabModule(const std::string& strModuleName);

	template <class T>
	bool Read(DWORD dwAddress, T& Value);
	template <class T>
	bool Write(DWORD dwAddress, const T& Value);

	HANDLE getHandle();
	DWORD getProcId();
	std::set<ModuleWrapper> getModules();

	void readAll();
};

#endif /* TOOLS_MEMORYMANAGER_HPP_ */
