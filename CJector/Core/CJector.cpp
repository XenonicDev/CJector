// Command Line Interface to CJector's Tools

#include <iostream>

#include "GenericTools.h"
#include "Win32Injector.h"

/* Usage:
 * Arguments (None for Command Line Interface)
 *  -1 [ Process Name ] [ DLL Path ]
 *  -2 [ Process ID ]   [ DLL Path ]
 */

int main(int ArgCount, char* ArgV[])
{
	Injector* Inj = new Injector();
	if (!Inj)
	{
		return -1;
	}

	// Command Line
	if (ArgCount > 2)
	{
		if (strcmp(ArgV[1], "-1") == 0)
		{
			std::cout << std::endl << "Injecting..." << std::endl;
			std::cout << ResultToString(Inj->Inject(ArgV[2], ArgV[3])) << std::endl;
		}

		else if (strcmp(ArgV[1], "-2") == 0)
		{
			std::cout << std::endl << "Injecting..." << std::endl;
			std::cout << ResultToString(Inj->Inject(std::stoi(ArgV[2]), ArgV[3])) << std::endl;
		}

		else
		{
			std::cout << std::endl << "Error Input Detected" << std::endl;
			return -1;
		}

		delete Inj;

		return 0;
	}

	// GUI
	else
	{
		unsigned int CLChoice;
		std::string DLLPath;

		system("CLS");
		std::cout << "- CJector Command Line Interface -" << std::endl << std::endl;
		std::cout << "Press 1 to Input Target by Name, 2 for Process ID: ";
		std::cin >> CLChoice;
		if (CLChoice == 1)
		{
			std::string ProcessName;
			std::cout << std::endl << "Target Process Name: ";
			std::cin >> ProcessName;

			std::cout << "DLL Path: ";
			std::cin >> DLLPath;

			std::cout << std::endl << "Injecting..." << std::endl;

			std::cout << std::endl << ResultToString(Inj->Inject(ProcessName, DLLPath)) << std::endl << std::endl;
		}

		else if (CLChoice == 2)
		{
			unsigned int ProcessID;
			std::cout << std::endl << "Target Process ID: ";
			std::cin >> ProcessID;

			std::cout << "DLL Path: ";
			std::cin >> DLLPath;

			std::cout << std::endl << "Injecting..." << std::endl;

			std::cout << std::endl << ResultToString(Inj->Inject(ProcessID, DLLPath)) << std::endl << std::endl;
		}

		else
		{
			std::cout << std::endl << std::endl << "Error Input Detected" << std::endl << std::endl;

			system("pause");
			return -1;
		}
	}

	delete Inj;

	system("pause");

	return 0;
}