#include <iostream>
#include <fstream>
#include "ArgsParser.h"
#include "Fill.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	auto args = ParseProgramArguments(argc, argv);
	if (!args)
	{
		cout << "Expected 2 arguments\n"
			 << "Arguments: <input file> <output file>" << endl;
		return 1;
	}

	std::string inputFileName{ args->inputFileName };
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		cout << "Unable to open " << inputFileName << endl;
		return 1;
	}

	try
	{
		std::string outputFileName{ args->outputFileName };
		std::ofstream outputFile(outputFileName);
		CanvasInfo canvasInfo = ReadCanvasFromFile(inputFile);
		std::shared_ptr<Canvas> filledCanvas = FillCanvas(canvasInfo);

		WriteToStream(*filledCanvas, outputFile);
	}
	catch (std::fstream::failure e)
	{
		cout << "Error: " << e.what() << endl;
		return 1;
	}
	
}
