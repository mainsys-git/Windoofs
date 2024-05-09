#pragma once
#include "includes.h"

class Log
{
public:
	static bool IsOpen;
	static void OpenConsole();
	static void LogMessage(const wchar_t* message, bool Succeed = true);
};
