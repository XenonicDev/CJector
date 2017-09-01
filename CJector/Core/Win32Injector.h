#pragma once

#include "GenericTools.h"

// Win32 API Injection Tools

class Injector
{
public:
	Injector() {}
	~Injector() {}

	InjectResult Inject(std::string ProcessName, std::string DLLPath);

private:
	Injector(const Injector&);
	void operator=(const Injector&);
};