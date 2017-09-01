// Command Line Interface to CJector's Tools

#include <iostream>

#include "GenericTools.h"
#include "Win32Injector.h"

int main()
{
	std::string ProcessName;
	std::string DLLPath;

	system("CLS");
	std::cout << "- CJector Command Line Interface -" << std::endl << std::endl;
	std::cout << "Target Process Name: ";
	std::cin >> ProcessName;
	std::cout << "DLL Path: ";
	std::cin >> DLLPath;

	std::cout << std::endl << "Executing..." << std::endl;

	Injector* Inj = new Injector();
	if (!Inj)
	{
		return -1;
	}

	std::cout << std::endl << ResultToString(Inj->Inject(ProcessName, DLLPath)) << std::endl << std::endl;

	system("pause");

	return 0;
}