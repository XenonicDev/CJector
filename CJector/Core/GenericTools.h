#pragma once

// How Long to Wait Before Marking the Injection as a Failure. 0 for Infinite Wait
#define INJECTION_TIMEOUT 0

#include <string>

enum InjectResult
{
	Success,
	Failure_DLLNotFound,
	Failure_ProcessNotFound,
	Failure_InjectionTimeout,
	Failure_Unknown
};

std::string ResultToString(InjectResult Result);

void FormatProcess(std::string& Process);
void FormatPath(std::string& Path);