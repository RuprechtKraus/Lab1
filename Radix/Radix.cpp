#include <iostream>
#include "ArgsParser.h"
#include "BaseCast.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	auto args = ParseProgramArguments(argc, argv);
	if (!args)
	{
		cout << "Expected 3 arguments\n"
			 << "Arguments: <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	if (!(IsValidBase(args->srcBase) &&
		  IsValidBase(args->destBase)))
	{
		cout << "Error: invalid notation\n"
			 << "Must be between 2 and 36" << endl;
		return 1;
	}

    int srcBase = std::stoi(args->srcBase);
    int destBase = std::stoi(args->destBase);
	string value = args->value;

	string result{};
	try
	{
		result = CastToBase(srcBase, destBase, value);
	}
	catch(std::exception e)
	{
		cout << "Error: " << e.what() << endl;
		return 1;
	}

	cout << result << endl;
}