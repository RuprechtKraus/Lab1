#pragma once
#include <string>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseProgramArguments(int argc, char* argv[])
{
	if (argc != 5)
		return std::nullopt;

	Args args{};
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}