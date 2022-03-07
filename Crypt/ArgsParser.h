#pragma once
#include <string>
#include <optional>
#include <algorithm>
#include <format>
#include <errno.h>

enum class CryptAction
{
	Encrypt,
	Decrypt
};

struct Args
{
	CryptAction cryptAction;
	std::string inputFileName;
	std::string outputFileName;
	int cryptKey;
};

CryptAction ValidateOperation(char* oper)
{
	if (std::strcmp(oper, "encrypt") == 0)
		return CryptAction::Encrypt;
	else if (std::strcmp(oper, "decrypt") == 0)
		return CryptAction::Decrypt;
	else
		throw std::invalid_argument(std::format("{} - no such operation", oper));
}

bool IsKeyInValidRange(int key)
{
	return key >= 0 && key <= 255;
}

bool IsKeyInteger(char* key, char* endPtr)
{
	return endPtr != key && *endPtr == '\0';
}

int ValidateKey(char* key)
{
	char* pEnd{};
	int validKey = std::strtol(key, &pEnd, 10);

	if (!IsKeyInteger(key, pEnd))
		throw std::invalid_argument("Key is not a valid integer number");
	else if (!IsKeyInValidRange(validKey))
		throw std::invalid_argument("Key must be between 0 and 255");
	else
		return validKey;
}

std::optional<Args> ParseProgramArguments(int argc, char* argv[])
{
	if (argc != 5)
		return std::nullopt;

	Args args{};
	args.cryptAction = ValidateOperation(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.cryptKey = ValidateKey(argv[4]);

	return args;
}