#pragma once
#include <string>
#include <algorithm>

bool IsValidBase(int base)
{
	return base >= 2 && base <= 36;
}

bool IsValidBase(const std::string& base)
{
	size_t pos{};
	int n{};

	try
	{
		n = std::stoi(base, &pos);
	}
	catch (std::exception e)
	{
		return false;
	}

	return n >= 2 && n <= 36 && pos == base.length();
}

bool IsExcessiveSymbol(int base, char c)
{
	if (base > 10)
	{
		int extraSymbols = base - 10;
		return (std::toupper(c) - 'A') >= extraSymbols;
	}
	else
	{
		return (static_cast<int>(c) - 48) >= base;
	}
}

bool IsInvalidChar(char c)
{
	return std::isspace(c) || std::ispunct(c);
}

bool IsValidNumber(int base, const std::string& value)
{
	auto begin = value.begin();
	auto end = value.end();

	if (value[0] == '-')
		begin++;

	bool result = !value.empty() && 
		!std::any_of(begin, end, [base](char c) { 
		return IsInvalidChar(c) || IsExcessiveSymbol(base, c); });

	return result;
}

// base - Основание, в которое нужно перевести число n
std::string IntToString(int n, int base)
{
	if (!IsValidBase(base))
		throw std::invalid_argument("Bad base");

	std::string result{};

	if (n)
	{
		for (int num = n; num > 0; num /= base)
		{
			int x = num % base;

			if (x >= 0 && x <= 9)
				result += ('0' + x);
			else
				result += ('A' + (x - 10));
		}
		std::reverse(result.begin(), result.end());
	}
	else
	{
		result = "0";
	}

	return result;
}

bool WillPowerOverflow(int num, int power)
{
	return power * std::log(num) >= std::log(std::numeric_limits<int>::max());
}

bool WillAdditionOverflow(int a, int b)
{
	return b > std::numeric_limits<int>::max() - a;
}

// base - Основание, в котором находится строка str
int StringToInt(const std::string& str, int base)
{
	if (!IsValidBase(base))
		throw std::invalid_argument("Bad base");

	int result{};
	int power = str.length() - 1;
	int i{};

	if (str[0] == '-')
	{
		power--; i++;
	}

	for (; i < str.length(); i++)
	{
		int symbol{};
		char c = str[i];

		if (std::isalpha(c))
			symbol = std::toupper(c) - ('A' - 10);
		else
			symbol = c - '0';

		if (WillPowerOverflow(base, power))
			throw std::overflow_error("Number is too big");
		int y = symbol * static_cast<int>(std::pow(base, power--));

		if (WillAdditionOverflow(result, y))
			throw std::overflow_error("Number is too big");
		result += y;
	}

	return result;
}

std::string CastToBase(int srcBase, int destBase, const std::string& value)
{
	if (!IsValidNumber(srcBase, value))
		throw std::invalid_argument("Invalid number");

	bool isNegative{ value[0] == '-' };
	std::string result{};

	if (isNegative)
		result = "-";

	int number = StringToInt(value, srcBase);
	result.append(IntToString(number, destBase));

	return result;
}