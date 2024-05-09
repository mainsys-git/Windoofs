#pragma once
class ProcessManagement
{
public:
	static void ForceClose(const char* processName);
	static bool IsProcessRunning(const char* processName);
};
