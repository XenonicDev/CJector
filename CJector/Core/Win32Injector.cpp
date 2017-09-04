#include "Win32Injector.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <TlHelp32.h>

InjectResult Injector::Inject(std::string ProcessName, std::string DLLPath)
{
	FormatPath(DLLPath);

	WIN32_FIND_DATA FindDLLData;
	HANDLE DLLHandle = FindFirstFile(DLLPath.c_str(), &FindDLLData);
	if (DLLHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(DLLHandle);

		return Failure_DLLNotFound;
	}

	// No Need for the DLL File Handle
	FindClose(DLLHandle);

	PROCESSENTRY32 Entry;
	Entry.dwSize = sizeof(Entry);

	HANDLE Flash = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	// Whether We Are Passing a Process Name or ID
	if (ProcessName.find("TARGET:") == std::string::npos)
	{
		bool Result = false;

		FormatProcess(ProcessName);

		if (Process32First(Flash, &Entry))
		{
			do
			{
				if (strcmp(Entry.szExeFile, ProcessName.c_str()) == 0)
				{
					Result = true;
				}
			}

			while (Process32Next(Flash, &Entry));
		}

		else
		{
			return Failure_Unknown;
		}

		if (!Result)
		{
			return Failure_ProcessNotFound;
		}
	}

	else
	{
		// Set the Process ID Manually
		Entry.th32ProcessID = std::stoi(ProcessName.substr(7));
	}

	HANDLE Target = OpenProcess(PROCESS_ALL_ACCESS, false, Entry.th32ProcessID);

	if ((Target != INVALID_HANDLE_VALUE) && (Target != NULL))
	{
		LPVOID LoadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
		LPVOID DLLPathPayload = VirtualAllocEx(Target, NULL, DLLPath.length(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		// Allocate the DLL Path on the Remote Process Heap
		WriteProcessMemory(Target, DLLPathPayload, DLLPath.c_str(), DLLPath.length(), nullptr);

		// Spin a Thread on the Target, Force the Target to Load Our DLL.
		HANDLE TargetRogueThread = CreateRemoteThread(Target, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryAddress, DLLPathPayload, 0, NULL);

		int Error = WaitForSingleObject(TargetRogueThread, INJECTION_TIMEOUT > 0 ? INJECTION_TIMEOUT : INFINITE);
		if (Error != 0)
		{
			if (Error == WAIT_TIMEOUT)
			{
				CloseHandle(Target);

				return Failure_InjectionTimeout;
			}

			CloseHandle(Target);

			return Failure_Unknown;
		}

		// Finished, the Target has Now Loaded Our DLL, Cleanup

		VirtualFreeEx(Target, DLLPathPayload, DLLPath.length(), MEM_RELEASE);
		CloseHandle(TargetRogueThread);
		CloseHandle(Target);

		return Success;
	}

	else
	{
		return Failure_ProcessNotFound;
	}
}

InjectResult Injector::Inject(unsigned int ProcessID, std::string DLLPath)
{
	PROCESSENTRY32 Entry;
	Entry.dwSize = sizeof(Entry);

	HANDLE Flash = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	return Inject("TARGET:" + std::to_string(ProcessID), DLLPath);
}