#include "LogConsole.h"

/**
 * Flag indicating whether the console is open.
 */
bool Log::IsOpen = false;

/**
 * Opens a console for logging.
 *
 * This function allocates a new console and redirects the standard output to it.
 */
void Log::OpenConsole()
{
    // Check if console allocation is successful
    if (!AllocConsole())
    {
        // Handle error: throw an exception if console allocation fails
        throw std::runtime_error("Failed to allocate console");
    }
    // Redirect the standard output to the new console
    freopen("CONOUT$", "w", stdout);
}

/**
 * Logs a message to the console with a specific color based on the success status.
 *
 * @param message The message to be logged.
 * @param succeed Whether the operation was successful.
 */
void Log::LogMessage(const wchar_t* message, bool succeed)
{
    // Get the standard output handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!hConsole)
    {
        // Handle error: throw an exception if getting the standard output handle fails
        throw std::runtime_error("Failed to get standard output handle");
    }

    // Define constants for console colors
    constexpr WORD SUCCESS_COLOR = FOREGROUND_GREEN;
    constexpr WORD FAILURE_COLOR = FOREGROUND_RED;
    constexpr WORD DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;

    // Set the console text color based on the success status
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

    // Reset the console text color to default
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    std::wcout << message << std::endl;
}