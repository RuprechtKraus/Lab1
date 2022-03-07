#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include "ArgsParser.h"
#include "Replace.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	auto args = ParseProgramArguments(argc, argv);
	if (!args)
	{
		cout << "Expected 4 arguments\n" 
			 << "Arguments: <input file> <output file> <search string> <replace string>" << endl;
		return 1;
	}

	std::ifstream inputFile(args->inputFileName);
	if (!inputFile.is_open())
	{
		cout << std::format("Unable to open {}", args->inputFileName) << endl;
		return 1;
	}

	std::ofstream outputFile(args->outputFileName);

	string searchString = args->searchString;
	string replaceString = args->replaceString;

	CopyAndReplace(inputFile, outputFile, searchString, replaceString);
	outputFile.flush();
}