#pragma once
#include <string>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseProgramArguments(int argc, char* argv[])
{
	if (argc != 3)
		return std::nullopt;

	Args args{};
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}