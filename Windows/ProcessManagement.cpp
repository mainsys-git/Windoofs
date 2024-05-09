#include "includes.h"

/**
 * Forces the closure of a process with the specified name.
 *
 * @param processName The name of the process to be closed.
 */
void ProcessManagement::ForceClose(const char* processName)
{
	// Create a snapshot of the current process list
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		// If the snapshot creation fails, exit the function
		return;
	}

	// Initialize the process entry structure
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	// Iterate through the process list
	if (Process32First(hSnapShot, &pEntry))
	{
		do
		{
			// Convert the executable file name to a wide string
			std::wstring exeFileName(pEntry.szExeFile);

			// Convert the target process name to a wide string
			std::wstring targetProcessName;
			int targetProcessNameLength = MultiByteToWideChar(CP_UTF8, 0, processName, -1, nullptr, 0);
			if (targetProcessNameLength > 0)
			{
				targetProcessName.resize(targetProcessNameLength - 1);
				MultiByteToWideChar(CP_UTF8, 0, processName, -1, &targetProcessName[0], targetProcessNameLength);
			}

			// Check if the current process matches the target process
			if (exeFileName == targetProcessName)
			{
				// Open the process with terminate permission
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pEntry.th32ProcessID);
				if (hProcess != nullptr)
				{
					// Terminate the process with exit code 9
					TerminateProcess(hProcess, 9);
					// Close the process handle
					CloseHandle(hProcess);
				}
			}
		}
		while (Process32Next(hSnapShot, &pEntry));
	}
	// Close the snapshot handle
	CloseHandle(hSnapShot);
}

bool ProcessManagement::IsProcessRunning(const char* processName)
{
	// Create a snapshot of the current process list
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		// If the snapshot creation fails, exit the function
		return false;
	}

	// Initialize the process entry structure
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	// Iterate through the process list
	if (Process32First(hSnapShot, &pEntry))
	{
		do
		{
			// Convert the executable file name to a wide string
			std::wstring exeFileName(pEntry.szExeFile);

			// Convert the target process name to a wide string
			std::wstring targetProcessName;
			int targetProcessNameLength = MultiByteToWideChar(CP_UTF8, 0, processName, -1, nullptr, 0);
			if (targetProcessNameLength > 0)
			{
				targetProcessName.resize(targetProcessNameLength - 1);
				MultiByteToWideChar(CP_UTF8, 0, processName, -1, &targetProcessName[0], targetProcessNameLength);
			}

			// Check if the current process matches the target process
			if (exeFileName == targetProcessName)
			{
				// Close the snapshot handle
				CloseHandle(hSnapShot);
				return true;
			}
		}
		while (Process32Next(hSnapShot, &pEntry));
	}
	// Close the snapshot handle
	CloseHandle(hSnapShot);
	return false;
}
