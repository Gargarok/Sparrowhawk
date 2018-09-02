/*
 * MemoryManager.cpp
 *
 *  Created on: 30 août 2018
 *      Author: Nous
 */

#include "MemoryManager.hpp"

ModuleWrapper::ModuleWrapper(MODULEENTRY32* module) {
	ModuleWrapper::module = module;
}

MODULEENTRY32* ModuleWrapper::getModule() {
	return ModuleWrapper::module;
}

bool ModuleWrapper::operator<(const ModuleWrapper& comp) const {
	char* compPath = comp.module -> szExePath;
	char* localPath = ModuleWrapper::module -> szExePath;
	return (localPath < compPath);
}


MemoryManager::MemoryManager() {
	m_hProcess = INVALID_HANDLE_VALUE;
	m_dwProcessId = 0;
	m_Modules.clear();
}

bool MemoryManager::Attach(const std::string& strProcessName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 ProcEntry;
		ProcEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapshot, &ProcEntry)) {
			if (ProcEntry.szExeFile == strProcessName) {
				// Targeted process has been found
				CloseHandle(hSnapshot);

				m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE,
						ProcEntry.th32ProcessID);
				m_dwProcessId = ProcEntry.th32ProcessID;

				return true;
			}

			// Iterate on the following processes
			while (Process32Next(hSnapshot, &ProcEntry)) {
				if (ProcEntry.szExeFile == strProcessName) {
					// Targeted process has been found
					CloseHandle(hSnapshot);

					m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE,
							ProcEntry.th32ProcessID);
					m_dwProcessId = ProcEntry.th32ProcessID;

					return true;
				}
			}
		}

		// The targeted process was not found : close handle and return false
		CloseHandle(hSnapshot);
	}
	return false;
}

bool MemoryManager::GrabModule(const std::string& strModuleName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
			m_dwProcessId);

	if (hSnapshot != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 ModEntry;
		ModEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &ModEntry)) {
			if (ModEntry.szModule == strModuleName) {
				// Targeted module has been found
				CloseHandle(hSnapshot);
				ModuleWrapper modWrapper = ModuleWrapper(&ModEntry);
				m_Modules.insert(modWrapper);
				return true;
			}

			// Iterate on the following modules
			while (Module32Next(hSnapshot, &ModEntry)) {
				if (ModEntry.szModule == strModuleName) {
					// Targeted module has been found
					CloseHandle(hSnapshot);
					ModuleWrapper modWrapper = ModuleWrapper(&ModEntry);
					m_Modules.insert(modWrapper);
					return true;
				}
			}
		}

		// The targeted module was not found : close handle and return false
		CloseHandle(hSnapshot);
	}
	return false;
}

// Read a value from memory and put it in outputSlot
// Returns true on success, false on failure
template<class T>
inline bool MemoryManager::Read(DWORD dwAddress, T& outputSlot) {
	return ReadProcessMemory(m_hProcess, reinterpret_cast<LPVOID>(dwAddress),
			outputSlot, sizeof(T), NULL) == TRUE;
}

// Write a Value in memory
// Returns true on success, false on failure
template<class T>
inline bool MemoryManager::Write(DWORD dwAddress, const T& inputValue) {
	return WriteProcessMemory(m_hProcess, reinterpret_cast<LPVOID>(dwAddress),
			inputValue, sizeof(T), NULL) == TRUE;
}

HANDLE MemoryManager::getHandle() {
	return m_hProcess;
}

DWORD MemoryManager::getProcId() {
	return m_dwProcessId;
}

std::set<ModuleWrapper> MemoryManager::getModules() {
	return m_Modules;
}

void MemoryManager::readAll() {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 ProcEntry;
		ProcEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapshot, &ProcEntry)) {
			std::string currentProcessName = ProcEntry.szExeFile;
			DWORD currentProcessId = ProcEntry.th32ProcessID;

			std::cout << "Process found ! Executable name : "
					<< currentProcessName << std::endl;

			HANDLE moduleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
					currentProcessId);
			if (moduleSnapshot != INVALID_HANDLE_VALUE) {
				MODULEENTRY32 ModEntry;
				ModEntry.dwSize = sizeof(MODULEENTRY32);

				if (Module32First(moduleSnapshot, &ModEntry)) {
					std::cout << "-- -- -- Module found ! Module name : "
							<< ModEntry.szModule << ", module path: "
							<< ModEntry.szExePath << std::endl;

					while (Module32Next(moduleSnapshot, &ModEntry)) {
						std::cout << "-- -- -- Module found ! Module name : "
								<< ModEntry.szModule << ", module path: "
								<< ModEntry.szExePath << std::endl;
					}
				}
				std::cout << "-- -- -- -- -- -- -- -- -- --" << std::endl;
				CloseHandle(moduleSnapshot);
			}

			// Iterate on the following processes
			while (Process32Next(hSnapshot, &ProcEntry)) {
				currentProcessName = ProcEntry.szExeFile;
				currentProcessId = ProcEntry.th32ProcessID;

				std::cout << "Process found ! Executable name : "
						<< currentProcessName << std::endl;

				HANDLE moduleSnapshot = CreateToolhelp32Snapshot(
						TH32CS_SNAPMODULE, currentProcessId);
				if (moduleSnapshot != INVALID_HANDLE_VALUE) {
					MODULEENTRY32 ModEntry;
					ModEntry.dwSize = sizeof(MODULEENTRY32);

					if (Module32First(moduleSnapshot, &ModEntry)) {
						std::cout << "-- -- -- Module found ! Module name : "
								<< ModEntry.szModule << ", module path: "
								<< ModEntry.szExePath << std::endl;

						while (Module32Next(moduleSnapshot, &ModEntry)) {
							std::cout
									<< "-- -- -- Module found ! Module name : "
									<< ModEntry.szModule << ", module path: "
									<< ModEntry.szExePath << std::endl;
						}
					}
					std::cout << "-- -- -- -- -- -- -- -- -- --" << std::endl;
					CloseHandle(moduleSnapshot);
				}
			}
		}
		CloseHandle(hSnapshot);
	}
}

