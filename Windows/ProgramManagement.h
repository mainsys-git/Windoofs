#pragma once
#include "includes.h"

class ProgramManagement
{
public:
	static void FindInstalledPrograms(std::vector<std::wstring>& programs);
	static bool IsProgramInstalled(const std::vector<std::wstring> installedPrograms, const std::wstring& programName);
	static void ProgramEntry();
};
