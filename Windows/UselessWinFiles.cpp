// includes.h is included for necessary library headers
#include "includes.h"

/**
 * SetPath function template to construct a path with the username.
 *
 * @tparam pathSize The size of the path buffer (default: MAX_PATH)
 * @tparam usernameSize The size of the username buffer (default: UNLEN + 1)
 * @param path The path template with a placeholder for the username
 * @return A wide string representing the constructed path
 */
template <size_t pathSize = MAX_PATH, size_t usernameSize = UNLEN + 1>
std::wstring SetPath(const wchar_t* path)
{
	wchar_t username[usernameSize];
	DWORD username_len = usernameSize;
	GetUserName(username, &username_len);

	wchar_t pathBuffer[pathSize];
	swprintf(pathBuffer, pathSize, path, username);

	return pathBuffer;
}

/**
 * BaseDelete function to delete a directory and its contents.
 *
 * @param dir The directory path to delete
 */
void Delete::BaseDelete(const std::filesystem::path& dir)
{
	for (const auto& entry : std::filesystem::directory_iterator(dir))
	{
		try
		{
			// Remove the file or directory
			remove_all(entry.path());
			// Update the GUI with the deleted file
			MainGUI::lbFiles->AppendString(entry.path().c_str());
			MainGUI::UpdateGui();

#if DEBUG
            // Log the deletion in debug mode
            Log::LogMessage(entry.path().c_str(), true);
#endif
		}
		catch (const std::filesystem::filesystem_error ex)
		{
#if DEBUG
            // Log the error in debug mode
            Log::LogMessage(entry.path().c_str(), false);
#endif
		}
	}
}

/**
 * DeleteFilesRecursevly function to delete files and directories recursively.
 *
 * @param dir The directory path to delete recursively
 */
void Delete::DeleteFilesRecursevly(const std::filesystem::path& dir)
{
	for (const auto& entry : std::filesystem::directory_iterator(dir))
	{
		try
		{
			if (is_directory(entry))
			{
				// Recursively delete the directory
				DeleteFilesRecursevly(entry.path());
			}
			else
			{
				try
				{
					// Remove the file
					std::filesystem::remove(entry.path());
					MainGUI::lbFiles->AppendString(entry.path().c_str());
					if (Log::IsOpen)
					{
						Log::LogMessage(entry.path().c_str(), true);
					}
					MainGUI::UpdateGui();
				}
				catch (const std::filesystem::filesystem_error ex)
				{
					if (Log::IsOpen)
						Log::LogMessage(entry.path().c_str(), false);
				}
			}
		}
		catch (const std::filesystem::filesystem_error ex)
		{
			if (Log::IsOpen)
				Log::LogMessage(entry.path().c_str(), false);
		}
		catch (const std::exception ex)
		{
			if (Log::IsOpen)
				Log::LogMessage(entry.path().c_str(), false);
		}
		catch (...)
		{
			if (Log::IsOpen)
				Log::LogMessage(entry.path().c_str(), false);
		}
	}
}

/**
 * DirectoryExists function to check if a directory exists.
 *
 * @param path The path to check
 * @return True if the directory exists, false otherwise
 */
bool Delete::DirectoryExists(const wchar_t* path)
{
	DWORD ftyp = GetFileAttributesW(path);
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

/**
 * DeleteTempFiles function to delete temporary files.
 */
void Delete::DeleteTempFiles()
{
	auto path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Temp\\");
	DeleteFilesRecursevly(path);
}

/**
 * DeleteWindowsTempFiles function to delete Windows temporary files.
 */
void Delete::DeleteWindowsTempFiles()
{
	wchar_t path[MAX_PATH];
	swprintf(path, MAX_PATH, L"C:\\Windows\\Temp\\");

	DeleteFilesRecursevly(path);
}

void Delete::DeleteWindowsInstallFiles()
{
	wchar_t path[MAX_PATH];
	swprintf(path, MAX_PATH, L"C:\\$WINDOWS.~BT");
	DeleteFilesRecursevly(path);

	swprintf(path, MAX_PATH, L"C:\\$Windows.~WS");
	DeleteFilesRecursevly(path);
}

/**
 * Deletes browser caches.
 */
void Delete::DeleteBrowserCaches()
{
	auto path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache\\");

	if (DirectoryExists(path.c_str()))
	{
		BaseDelete(path);
	}

	path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cache\\");
	if (DirectoryExists(path.c_str()))
	{
		BaseDelete(path);
	}


	path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Opera Software\\Opera Stable\\Cache\\");
	if (DirectoryExists(path.c_str()))
	{
		BaseDelete(path);
	}


	path = SetPath(L"C:\\Users\\%s\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\");
	if (DirectoryExists(path.c_str()))
	{
		BaseDelete(path);
	}

	path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cache\\");
	if (DirectoryExists(path.c_str()))
	{
		BaseDelete(path);
	}
}

/*void Delete::DeleteWindowsLogs()
{
    Log::OpenConsole();

    wchar_t pathWindows[MAX_PATH];
    wchar_t pathSystem32[MAX_PATH];
    swprintf(pathSystem32, MAX_PATH, L"C:\\Windows\\System32\\LogFiles\\");
    swprintf(pathWindows, MAX_PATH, L"C:\\Windows\\Logs\\");
    std::wcout << pathWindows << std::endl;
    std::wcout << pathSystem32 << std::endl;

    DeleteFilesRecursevly(pathWindows);
    DeleteFilesRecursevly(pathSystem32);
}*/


/**
 * DeleteCookies function to delete cookies.
 */
void Delete::DeleteCookies()
{
	auto path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Network\\");
	BaseDelete(path);

	path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Network\\");
	BaseDelete(path);

	path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\Opera Software\\Opera Stable\\Network\\");
	BaseDelete(path);

	path = SetPath(L"C:\\Users\\%s\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\");
	BaseDelete(path);

	path = SetPath(L"C:\\Users\\%s\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Network\\");
	BaseDelete(path);
}

/**
 * DeleteRecycleBin function to delete the Recycle Bin.
 */
void Delete::DeleteRecycleBin()
{
	SHEmptyRecycleBin(nullptr, nullptr, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
	if (GetLastError() == ERROR_SUCCESS)
	{
		MainGUI::lbFiles->AppendString(L"Recycle Bin cleared!");
		MainGUI::UpdateGui();
	}
	else
	{
		MainGUI::lbFiles->AppendString(L"Recycle Bin could not be cleared!");
		MainGUI::UpdateGui();
	}
#if DEBUG
    Log::LogMessage(L"Recycle Bin cleared!", true);
#endif
}
