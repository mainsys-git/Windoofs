#include "ProgramManagement.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

void ProgramManagement::FindInstalledPrograms(std::vector<std::wstring>& programs)
{
	HKEY hUninstallKey = nullptr;
	LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0,
	                            KEY_READ, &hUninstallKey);

	if (lResult != ERROR_SUCCESS)
	{
		std::cerr << "Unable to open Uninstall key!\n";
		return;
	}

	DWORD dwIndex = 0;
	wchar_t szSubKeyName[256];
	DWORD dwSize = std::size(szSubKeyName);
	while (RegEnumKeyEx(hUninstallKey, dwIndex, szSubKeyName, &dwSize, nullptr, nullptr, nullptr, nullptr) ==
		ERROR_SUCCESS)
	{
		HKEY hAppKey = nullptr;
		if (RegOpenKeyEx(hUninstallKey, szSubKeyName, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS)
		{
			wchar_t szDisplayName[256];
			DWORD dwType = 0;
			DWORD dwSize = sizeof(szDisplayName);
			if (RegQueryValueEx(hAppKey, L"DisplayName", nullptr, &dwType, reinterpret_cast<LPBYTE>(szDisplayName),
			                    &dwSize) ==
				ERROR_SUCCESS)
			{
				programs.emplace_back(szDisplayName);
			}
			RegCloseKey(hAppKey);
		}
		dwSize = std::size(szSubKeyName);
		dwIndex++;
	}
	RegCloseKey(hUninstallKey);
}

bool ProgramManagement::IsProgramInstalled(const std::vector<std::wstring>& installed_programs,
                                           const std::wstring& program_name)
{
	for (const auto& installedProgram : installed_programs)
	{
		if (installedProgram == program_name)
		{
			return true;
		}
	}
	return false;
}

void ProgramManagement::ProgramEntry()
{
	std::vector<std::wstring> installedPrograms;
	FindInstalledPrograms(installedPrograms);

	for (const auto& program : installedPrograms)
	{
		std::wcout << program << "\n";
	}
}

void ProgramManagement::UninstallProgram(const std::wstring& program_name)
{
}
