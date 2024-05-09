#include "LogConsole.h"

bool Log::IsOpen = false;

void Log::OpenConsole()
{
	// Check if console allocation is successful
	if (!AllocConsole())
	{
		// Handle error
		throw std::runtime_error("Failed to allocate console");
	}
	freopen("CONOUT$", "w", stdout);
}

void Log::LogMessage(const wchar_t* message, bool succeed)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hConsole)
	{
		// Handle error
		throw std::runtime_error("Failed to get standard output handle");
	}

	// Use constants for console colors
	constexpr WORD SUCCESS_COLOR = FOREGROUND_GREEN;
	constexpr WORD FAILURE_COLOR = FOREGROUND_RED;
	constexpr WORD DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;

	if (succeed)
	{
		SetConsoleTextAttribute(hConsole, SUCCESS_COLOR);
		std::wcout << "\nDeleted:\n";
	}
	else
	{
		SetConsoleTextAttribute(hConsole, FAILURE_COLOR);
		std::wcout << "\nCouldn't delete:\n";
	}

	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
	std::wcout << message << std::endl;
}
