#pragma once
namespace std::filesystem
{
	class path;
}

class Delete
{
public:
	static void BaseDelete(const std::filesystem::path& dir);
	static void DeleteFilesRecursevly(const std::filesystem::path& dir);
	static bool DirectoryExists(const wchar_t* path);
	static void DeleteTempFiles();
	static void DeleteWindowsTempFiles();
	static void DeleteWindowsInstallFiles();
	//	static void DeleteWindowsLogs(); 
	static void DeleteBrowserCaches();
	static void DeleteCookies();
	static void DeleteRecycleBin();
};
