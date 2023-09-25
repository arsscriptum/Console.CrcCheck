
//==============================================================================
//
//     main.cpp
//
//============================================================================
//  Copyright (C) Guilaume Plante 2020 <guillaumeplante.qc@gmail.com>
//==============================================================================



#include "stdafx.h"
#include "cmdline.h"
#include "Shlwapi.h"
#include "log.h"


#include <codecvt>
#include <locale>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <regex>
#include <filesystem>
#include <iostream>
#include <sstream>
#include "crc.h"

using namespace std;

#pragma message( "Compiling " __FILE__ )
#pragma message( "Last modified on " __TIMESTAMP__ )




void banner();
void usage();

int main(int argc, TCHAR** argv, TCHAR envp)
{

#ifdef UNICODE
	const char** argn = (const char**)C::Convert::allocate_argn(argc, argv);
#else
	char** argn = argv;
#endif // UNICODE

	CmdLineUtil::getInstance()->initializeCmdlineParser(argc, argn);

	CmdlineParser* inputParser = CmdLineUtil::getInstance()->getInputParser();

	CmdlineOption cmdlineOptionHelp({ "-h", "--help" }, "display this help");
	CmdlineOption cmdlineOptionNoBanner({ "-n", "--nobanner" }, "no banner");
	CmdlineOption cmdlineOptionFile({ "-f", "--file" }, "file path");


	inputParser->addOption(cmdlineOptionHelp);
	inputParser->addOption(cmdlineOptionNoBanner);
	inputParser->addOption(cmdlineOptionFile); 


	bool optHelp = inputParser->isSet(cmdlineOptionHelp);
	bool optNoBanner = inputParser->isSet(cmdlineOptionNoBanner);
	bool optFile= inputParser->isSet(cmdlineOptionFile);
	
	if(optNoBanner == false){
		banner();
	}
	if(optHelp){
		usage();
		return 0;
	}

	if(inputParser->cmdOptionExists("-f")){
		std::string valueName = inputParser->getCmdOption("-f");
		int crc = 0;

		FILE *fileptr;
		char *buffer;
		long filelen;

		fileptr = fopen(valueName.c_str(), "rb");  // Open the file in binary mode
		fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
		filelen = ftell(fileptr);             // Get the current byte offset in the file
		rewind(fileptr);                      // Jump back to the beginning of the file

		buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
		fread(buffer, filelen, 1, fileptr); // Read in the entire file
		fclose(fileptr); // Close the file

		const char* cData = argv[1];
		int nSize = atoi(argv[2]);

		crc = crc16((uint8_t*) buffer, filelen);

	  	printf("%u", crc);
	}
	
	return 0;
}




void banner() {
	std::wcout << std::endl;
	printf("crccheck.exe v1.0 - do a crc check on a file\n");
	printf("Built on %s\n", __TIMESTAMP__);
	printf("Copyright (C) 2000-2021 Guillaume Plante\n");
	std::wcout << std::endl;
}
void usage() {
	printf("Usage: crccheck.exe [-h][-n][-f] file path \n");
	printf("   -h          Help\n");
	printf("   -n          No banner\n");
	printf("   -f file     file path\n");
	std::wcout << std::endl;
}


