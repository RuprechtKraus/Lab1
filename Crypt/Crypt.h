#pragma once
#include <string>
#include <fstream>
#include <functional>

using CryptFunction = std::function<std::string(const std::string& str, int key)>;
bool EncryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key);
bool DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key);
bool Crypt(std::ifstream& inputFile, std::ofstream& outputFile, int key, const CryptFunction& cryptFunc);

char EncryptChar(char ch, int key)
{
	ch ^= key;
	char c1 = (ch >> 2) & 0b00100000;
	char c2 = (ch >> 5) & 0b00000010;
	char c3 = (ch >> 5) & 0b00000001;
	char c4 = (ch << 3) & 0b10000000;
	char c5 = (ch << 3) & 0b01000000;
	char c6 = (ch << 2) & 0b00010000;
	char c7 = (ch << 2) & 0b00001000;
	char c8 = (ch << 2) & 0b00000100;
	char encryptedChar = c1 | c2 | c3 | c4 | c5 | c6 | c7 | c8;

	return encryptedChar;
}

char DecryptChar(char ch, int key)
{
	char c1 = (ch << 2) & 0b10000000;
	char c2 = (ch << 5) & 0b01000000;
	char c3 = (ch << 5) & 0b00100000;
	char c4 = (ch >> 3) & 0b00010000;
	char c5 = (ch >> 3) & 0b00001000;
	char c6 = (ch >> 2) & 0b00000100;
	char c7 = (ch >> 2) & 0b00000010;
	char c8 = (ch >> 2) & 0b00000001;
	char decryptedChar = c1 | c2 | c3 | c4 | c5 | c6 | c7 | c8;
	decryptedChar ^= key;

	return decryptedChar;
}

std::string EncryptString(const std::string& str, int key)
{
	using namespace std::placeholders;
	std::string encryptedStr{};
	auto encryptChar = std::bind(EncryptChar, _1, key);
	std::transform(str.cbegin(), str.cend(), std::back_inserter(encryptedStr), encryptChar);

	return encryptedStr;
}

std::string DecryptString(const std::string& str, int key)
{
	using namespace std::placeholders;
	std::string decryptedStr{};
	auto decryptChar = std::bind(DecryptChar, _1, key);
	std::transform(str.cbegin(), str.cend(), std::back_inserter(decryptedStr), decryptChar);

	return decryptedStr;
}

bool EncryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	return Crypt(inputFile, outputFile, key, EncryptString);
}

bool DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	return Crypt(inputFile, outputFile, key, DecryptString);
}

bool Crypt(std::ifstream& inputFile, std::ofstream& outputFile, int key, const CryptFunction& cryptFunc)
{
	std::string line{};

	while (std::getline(inputFile, line))
		outputFile << cryptFunc(line, key) << "\n";

	if (!outputFile)
		return false;

	return true;
}