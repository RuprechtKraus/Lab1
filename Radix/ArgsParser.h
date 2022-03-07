#pragma once
#include <string>
#include <optional>

struct Args
{
	std::string srcBase;
	std::string destBase;
	std::string value;
};

std::optional<Args> ParseProgramArguments(int argc, char* argv[])
{
	if (argc != 4)
		return std::nullopt;

	Args args{};
	args.srcBase = argv[1];
	args.destBase = argv[2];
	args.value = argv[3];

	return args;
}