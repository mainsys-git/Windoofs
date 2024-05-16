#include "ProgramManagement.h"

void ProgramManagement::FindInstalledPrograms(std::vector<std::wstring>& programs)
{
    HKEY hUninstallKey = NULL;
    LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hUninstallKey);

    if (lResult != ERROR_SUCCESS) {
        std::cerr << "Unable to open Uninstall key!" << std::endl;
        return;
    }

    DWORD dwIndex = 0;
    wchar_t szSubKeyName[256];
    DWORD dwSize = std::size(szSubKeyName);
    while (RegEnumKeyEx(hUninstallKey, dwIndex, szSubKeyName, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
        HKEY hAppKey = NULL;
        if (RegOpenKeyEx(hUninstallKey, szSubKeyName, 0, KEY_READ, &hAppKey) == ERROR_SUCCESS) {
            wchar_t szDisplayName[256];
            DWORD dwType = 0;
            DWORD dwSize = sizeof(szDisplayName);
            if (RegQueryValueEx(hAppKey, L"DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwSize) == ERROR_SUCCESS) {
                programs.push_back(szDisplayName);
            }
            RegCloseKey(hAppKey);
        }
        dwSize = sizeof(szSubKeyName) / sizeof(szSubKeyName[0]);
        dwIndex++;
    }
    RegCloseKey(hUninstallKey);
}

bool ProgramManagement::IsProgramInstalled(const std::vector<std::wstring> installedPrograms,
	const std::wstring& programName)
{
    for(const auto& installedProgram : installedPrograms)
    {
	    if(installedProgram == programName)
	    {
			return true;
	    }

		return false;
    }
}

void ProgramManagement::ProgramEntry()
{
	std::vector<std::wstring> installedPrograms;
    FindInstalledPrograms(installedPrograms);

	HKEY hKey = NULL;
	LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE", 0, KEY_READ, &hKey);

	if (lResult != ERROR_SUCCESS)
    {
		std::cerr << "Unable to open SOFTWARE key!\n";
		return;
	}

	DWORD dwIndex = 0;
	wchar_t szSubKeyName[256];
	DWORD dwSize = std::size(szSubKeyName);

	while (RegEnumKeyEx(hKey, dwIndex, szSubKeyName, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{
			if(IsProgramInstalled(installedPrograms, szSubKeyName))
			{
				std::wcout << szSubKeyName << "\n";
			}

			dwSize = std::size(szSubKeyName);
			dwIndex++;
	}
    RegCloseKey(hKey);
}
