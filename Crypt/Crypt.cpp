#include <iostream>
#include <fstream>
#include <optional>
#include <format>
#include "ArgsParser.h"
#include "Crypt.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	std::optional<Args> args{};

	try
	{
		args = ParseProgramArguments(argc, argv);
	}
	catch (std::invalid_argument ia)
	{
		cout << "Error: " << ia.what() << endl;
		return 1;
	}

	if (!args)
	{
		cout << "Expected 5 arguments\n"
			 << "Arguments: encrypt/decrypt <input file> <output file> <key>" << endl;
		return 1;
	}

	std::string inputFileName = args->inputFileName;
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "Unable to open " << inputFileName << endl;
		return 1;
	}

	std::string outputFileName = args->outputFileName;
	std::ofstream outputFile(outputFileName);
	int cryptKey = args->cryptKey;
	bool cryptSuccessful{};

	switch (args->cryptAction)
	{	
	case CryptAction::Encrypt:
		cryptSuccessful = EncryptFile(inputFile, outputFile, cryptKey);
		if (!cryptSuccessful)
			cout << "Error during encryption" << endl;
		break;
	case CryptAction::Decrypt:
		cryptSuccessful = DecryptFile(inputFile, outputFile, cryptKey);
		if (!cryptSuccessful)
			cout << "Error during decryption" << endl;
		break;
	default:
		break;
	}
}
