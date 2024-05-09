#include "includes.h"


void ProcessManagement::ForceClose(const char* processName)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
		return;

	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapShot, &pEntry))
	{
		do
		{
			std::wstring exeFileName(pEntry.szExeFile);
			std::wstring targetProcessName;
			int targetProcessNameLength = MultiByteToWideChar(CP_UTF8, 0, processName, -1, nullptr, 0);
			if (targetProcessNameLength > 0)
			{
				targetProcessName.resize(targetProcessNameLength - 1);
				MultiByteToWideChar(CP_UTF8, 0, processName, -1, &targetProcessName[0], targetProcessNameLength);
			}

			if (exeFileName == targetProcessName)
			{
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pEntry.th32ProcessID);
				if (hProcess != nullptr)
				{
					TerminateProcess(hProcess, 9);
					CloseHandle(hProcess);
				}
			}
		}
		while (Process32Next(hSnapShot, &pEntry));
	}
	CloseHandle(hSnapShot);
}
