#pragma once
#include "includes.h"

class ProgramManagement
{
public:
	static void FindInstalledPrograms(std::vector<std::wstring>& programs);
	static bool IsProgramInstalled(const std::vector<std::wstring>& installed_programs,
	                               const std::wstring& program_name);
	static void ProgramEntry();
	static void UninstallProgram(const std::wstring& program_name);
};
