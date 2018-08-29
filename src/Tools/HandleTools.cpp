/*
 * HandleTools.cpp
 *
 *  Created on: 28 août 2018
 *      Author: Nous
 */

#include "HandleTools.hpp"

// Example of algorithm to open an handle to a specific process based on his name.
// Returns the HANDLE to the process. (INVALID_HANDLE_VALUE if not found)
HANDLE openHandle(const std::string& ProcessName)
{
    // First of all we create a snapshot handle specific for processes
    // (notice the usage of TH32CS_SNAPPROCESS) so we are able to call Process32First/Next
    // Remeber to close it when you don't use it anymore!
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    // Check if the snapshot created is valid
    if (hSnapshot == INVALID_HANDLE_VALUE) return INVALID_HANDLE_VALUE;

    // Create the helper struct that will contain all the infos about the current process
    // while we loop through all the running processes
    PROCESSENTRY32 ProcEntry;
    // Remember to set the dwSize member of ProcEntry to sizeof(PROCESSENTRY32)
    ProcEntry.dwSize = sizeof(PROCESSENTRY32);

    // Call Process32First
    if (Process32First(hSnapshot, &ProcEntry))
    {
        // Notice that you have to enable Multi-Byte character set in order
        // to avoid converting everything.
        // strcmp is not the only way to compare 2 strings ofc, work with your imagination
        if (!strcmp(ProcEntry.szExeFile, ProcessName.c_str()))
        {
            // If we are here it means that the process has been found, we can
            // open an handle to it and return it
            // But first of all we have to close the snapshot handle!
            CloseHandle(hSnapshot);
            // Return the handle opened to the process with OpenProcess
            // (Notice the usage of PROCESS_ALL_ACCESS flag in order to grant read/write privileges)
            std::cout << "First processed looped through: " << ProcEntry.szExeFile << std::endl;
            return OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcEntry.th32ProcessID);
        }
    }
    else
    {
        // If the Process32First call failed, it means that there is no
        // process running in the first place, we can return directly.
        CloseHandle(hSnapshot);
        return INVALID_HANDLE_VALUE;
    }

    // If we are here it means that the Process32First call returned TRUE, but the first process
    // wasn't the process that we were searching for. Now we can loop through the processes
    // using Process32Next
    while (Process32Next(hSnapshot, &ProcEntry))
    {
        // We do the same check we did for Process32First
        if (!strcmp(ProcEntry.szExeFile, ProcessName.c_str()))
        {
            // If we are here it means that the process has been found, we can
            // open an handle to it and return it
            // But first of all we have to close the snapshot handle!
            CloseHandle(hSnapshot);
            // Return the handle opened to the process with OpenProcess
            // (Notice the usage of PROCESS_ALL_ACCESS flag in order to grant read/write privileges)
            std::cout << "Next processed looped through: " << ProcEntry.szExeFile << std::endl;
            return OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcEntry.th32ProcessID);
        }
    }
    // Continue loop while the Process32Next call returns TRUE meaning that there are still processes to check

    // If we are here it means that the process has not been found or that there are no processes to scan for anymore.
    // We can close the snapshot handle and return fail value.
    CloseHandle(hSnapshot);
    return INVALID_HANDLE_VALUE;
}
