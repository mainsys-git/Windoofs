#pragma once
namespace std::filesystem
{
	class path;
}

class Delete
{
public:
	static void DeleteFiles(const std::filesystem::path& dir);
	static void DeleteFilesRecursively(const std::filesystem::path& dir);
	static bool DirectoryExists(const wchar_t* path);
	static void DeleteTempFiles();
	static void DeleteWindowsTempFiles();
	static void DeleteWindowsInstallationFiles();
	//	static void DeleteWindowsLogs(); 
	static void DeleteBrowserCaches();
	static void DeleteCookies();
	static void DeleteRecycleBin();
};
