// Retro Launcher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MemoryPatch.h"
#include <vector>


int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "http://www.ehmtheblueline.com" << std::endl
			  << std::endl
			  << "EHM Retro Launcher v1.5.1" << std::endl
			  << "by Archibalduk" << std::endl
			  << std::endl;

	// Load EHM and open a process
	MemoryPatch::loadEHM(argc, argv);
	
	// Create a vector of changes to be made
	std::vector<MemoryPatch> patch;
	patch.push_back(MemoryPatch(0x89A1E5, 1901, 2, "Minimum schedule year"));
	patch.push_back(MemoryPatch(0x89A953, 1901, 2, "Minimum schedule year"));
	patch.push_back(MemoryPatch(0x89AD5A, 1901, 2, "Minimum schedule year"));

	// Error flag
	bool error = false;

	// Apply the patch
	for(auto itr = patch.begin(); itr < patch.end(); ++itr)
		if(itr->apply() == false)
			error = true;

	// If the patch was successful
	if(error == false)
		return 0;

	// If the patch was unsuccessful
	else {
		std::cout << std::endl
				  << "ERROR: UNABLE TO APPLY THE PATCH" << std::endl
				  << "Press ENTER to close this window.";
		std::cin.get();
		return 1;
	}
}

