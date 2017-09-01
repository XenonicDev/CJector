#include "GenericTools.h"

std::string ResultToString(InjectResult Result)
{
	switch (Result)
	{
	case Success: return std::string("Success");
	case Failure_DLLNotFound: return std::string("Failure: Could Not Locate Specified DLL");
	case Failure_ProcessNotFound: return std::string("Failure: Process Not Found");
	case Failure_InjectionTimeout: return std::string("Failure: Injector Timed Out");
	default: return std::string("Failure: Encountered Unknown Failure");
	}
}

void FormatProcess(std::string& Process)
{
	if (Process.empty())
	{
		Process = std::string("ERROR");
	}

	if (Process.find(".exe", 0) == std::string::npos)
	{
		Process.append(".exe");
	}
}

void FormatPath(std::string& Path)
{
	if (Path.empty())
	{
		Path = std::string("ERROR");
	}

	if (Path.find(".dll", 0) == std::string::npos)
	{
		Path.append(".dll");
	}
}