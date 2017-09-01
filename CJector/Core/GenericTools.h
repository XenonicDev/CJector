#pragma once

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